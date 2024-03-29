/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:34:32 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 21:00:20 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands/commands.hpp"

DEFINE_CMD(Topic, {
	ENSURE_AUTH();

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

	if (channel->getTopicForOpsOnly() &&
		client->getModes().find('o') == std::string::npos)
	{
		msg.replyError(ERR_CHANOPRIVSNEEDED, ":You're not a channel operator");
		return ;
	}

	ITER_CHANNEL_CLIENTS(*channel)
	{
		CLIENT()->sendRaw(":" + client->getIdentifier() + " TOPIC " +
			channel->getName() + " :" + PARAM(1));
	}
})
