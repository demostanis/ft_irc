/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:11:49 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/17 19:38:59 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Part, {
	ENSURE_AUTH();

	std::string		channelName;
	BNFFind			channelNames;
	std::string		channelNamesRaw;
	std::string		reason;
	IrcChannel		*channel;

	if (N_PARAMS() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	channelNamesRaw = PARAM(0);
	listParser.parse(channelNamesRaw);
	channelNames = listParser["word"];
	reason = "quit";
	if (N_PARAMS() >= 2)
		reason = PARAM(1);

	for (BNFFind::iterator channelName = channelNames.begin();
		channelName != channelNames.end(); ++channelName)
	{
		channel = server.getChannel(channelName->string());
		if (channel != NULL)
		{
			if (!client->isInChannel(channel))
			{
				msg.replyError(ERR_NOTONCHANNEL, ":You're not on that channel");
				return ;
			}

			ITER_CHANNEL_CLIENTS(*channel)
			{
				CLIENT()->sendRaw(":" + client->getIdentifier() +
					" PART " + *channelName + " :" + reason);
			}
			client->removeChannel(channel);
			channel->remove(client);
		}
		else
			msg.replyError(ERR_NOSUCHCHANNEL, ":No such channel");
	}
})
