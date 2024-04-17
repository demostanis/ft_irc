/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/17 19:33:28 by nlaerema         ###   ########.fr       */
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

	std::string		channelNamesRaw;
	std::string		keyRaw;
	BNFFind			channelNames;
	BNFFind			channelPasswords;
	IrcChannel		*channel;

	if (N_PARAMS() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	channelNamesRaw = PARAM(0);
	listParser.parse(channelNamesRaw);
	channelNames = listParser["word"];
	if (N_PARAMS() >= 2)
	{
		keyRaw = PARAM(1);
		listParser.parse(keyRaw);
		channelPasswords = listParser["word"];
	}

	unsigned int	chanlimit;
	kdo::convert(chanlimit, server.getConfig()["chanlimit"]);
	if (client->getChannels().size() + channelNames.size() >= chanlimit)
	{
		msg.replyError(ERR_TOOMANYCHANNELS, ":Too many channels");
		return ;
	}

	unsigned int	channellen;
	kdo::convert(channellen, server.getConfig()["channellen"]);

	BNFFind::iterator	channelName = channelNames.begin();
	for (; channelName != channelNames.end(); channelName++)
	{
		if (!IrcChannel::isValidName(channelName->string(), channellen))
		{
			msg.replyError(ERR_BADCHANNAME, *channelName + " :Illegal channel name");
			return ;
		}
	}
	
	channelName = channelNames.begin();
	for (; channelName != channelNames.end(); channelName++)
	{
		channel = server.createChannelIfNeeded(channelName->string());
		if (client->isInChannel(channel))
			continue ;
		if (channel->getClientLimit() != -1 &&
			(int)(channel->getClients().size() + 1) >= channel->getClientLimit())
		{
			msg.replyError(ERR_CHANNELISFULL, *channelName + " :Cannot join channel (+l)");
			continue ;
		}
		std::string password = channel->getPassword();
		if (!password.empty())
		{
			if (channelPasswords.size() == 0 || password != channelPasswords[0])
			{
				msg.replyError(ERR_BADCHANNELKEY, *channelName + " :Cannot join channel (+k)");
				continue ;
			}
			channelPasswords.erase(channelPasswords.begin());
		}
		if (channel->isInvitationOnly())
		{
			if (!channel->isInvited(client))
			{
				msg.replyError(ERR_INVITEONLYCHAN, *channelName + " :Cannot join channel (+i)");
				continue ;
			}
			channel->wasInvited(client);
		}

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
