/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 19:57:01 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

static void	sendNames(IrcClient *client, IrcChannel &channel)
{
	std::string	usernames;

	ITER_CHANNEL_CLIENTS(channel)
	{
		// TODO: add @ if op
		usernames += "@" + CLIENT()->getNick();
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
})
