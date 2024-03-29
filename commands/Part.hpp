/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:11:49 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 12:25:31 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Part, {
	ENSURE_AUTH();

	std::string	channelName;
	std::string	reason;
	IrcChannel	*channel;

	if (N_PARAMS() < 2)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	// TODO: handle many
	channelName = PARAM(0);
	reason = PARAM(1);
	channel = server.getChannel(channelName);
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
				" PART " + channelName + " :" + reason);
		}
		client->removeChannel(channel);
		channel->remove(client);
	}
	else
		msg.replyError(ERR_NOSUCHCHANNEL, ":No such channel");
})
