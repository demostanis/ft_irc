/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 22:21:11 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

static void	sendNames(IrcClient *client, IrcChannel &channel)
{
	std::string	usernames;

	ITER_CHANNEL_CLIENTS(channel)
	{
		if (CLIENT()->getModes().find('o') != std::string::npos)
			usernames += "@";
		usernames += CLIENT()->getNick();
		if (clients != channel.getClients().end() - 1)
			usernames += " ";
	}

	client->sendRpl(RPL_NAMREPLY, "= " + channel.getName() + " :" + usernames);
	client->sendRpl(RPL_ENDOFNAMES, channel.getName() + " :End of /NAMES list");
}

DEFINE_CMD(Join, {
	ENSURE_AUTH();

	std::string					channelNamesRaw;
	std::vector<std::string>	channelNames;
	IrcChannel					*channel;

	if (N_PARAMS() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	channelNamesRaw = PARAM(0);
	channelNames = kdo::splitlist(channelNamesRaw);

	unsigned int	chanlimit;
	kdo::convert(chanlimit, server.getConfig()["chanlimit"]);
	if (client->getChannels().size() + channelNames.size() >= chanlimit)
	{
		msg.replyError(ERR_TOOMANYCHANNELS, ":Too many channels");
		return ;
	}

	std::vector<std::string>::iterator	channelName = channelNames.begin();
	for (; channelName != channelNames.end(); channelName++)
	{
		if (!IrcChannel::isValidName(*channelName))
		{
			msg.replyError(ERR_BADCHANNAME, ":Illegal channel name");
			return ;
		}
	}
	
	channelName = channelNames.begin();
	for (; channelName != channelNames.end(); channelName++)
	{
		channel = server.createChannelIfNeeded(*channelName);
		if ((int)(channel->getClients().size() + 1) >= channel->getClientLimit())
		{
			msg.replyError(ERR_CHANNELISFULL, ":Cannot join channel (+l)");
		}
		else
		{
			client->addChannel(channel);
			channel->add(client);

			ITER_CHANNEL_CLIENTS(*channel)
			{
				CLIENT()->sendRaw(":" + client->getIdentifier() +
					" JOIN " + *channelName);
			}

			if (!channel->getTopic().empty())
				client->sendRpl(RPL_TOPIC, *channelName + " :" + channel->getTopic());
			sendNames(client, *channel);
		}
	}
})
