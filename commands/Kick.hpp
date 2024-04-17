/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:16:28 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/17 19:41:16 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands/commands.hpp"

DEFINE_CMD(Kick, {
	ENSURE_AUTH();
	ENSURE_OP();

	if (N_PARAMS() < 2)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	std::string	channelName = PARAM(0);
	IrcChannel	*channel = server.getChannel(channelName);
	if (channel == NULL)
	{
		msg.replyError(ERR_NOSUCHCHANNEL, ":No such channel");
		return ;
	}
	if (!client->isInChannel(channel))
	{
		msg.replyError(ERR_NOTONCHANNEL, ":You're not on that channel");
		return ;
	}

	IrcClient	*kickedClient = NULL;
	std::string	kicketeesRaw = PARAM(1);
	BNFFind		kicketees;

	listParser.parse(kicketeesRaw);
	kicketees = listParser["word"];

	for (BNFFind::iterator	kicketee = kicketees.begin();
		kicketee != kicketees.end(); ++kicketee)
	{
		ITER_CHANNEL_CLIENTS(*channel)
		{
			if (CLIENT()->getNick() == *kicketee)
			{
				kickedClient = CLIENT();
				break ;
			}
		}
		if (kickedClient == NULL)
		{
			msg.replyError(ERR_USERNOTINCHANNEL, ":They aren't on that channel");
			return ;
		}

		kickedClient->removeChannel(channel);
		channel->remove(kickedClient);

		std::string		reason = "Breton";
		if (N_PARAMS() >= 3)
			reason = PARAM(2);
		kickedClient->sendRaw(":" + client->getIdentifier() + " KICK " +
			channelName + " " + *kicketee + " :" + reason);
	}
})
