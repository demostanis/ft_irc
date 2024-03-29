/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:35:35 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 14:37:52 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands/commands.hpp"

DEFINE_CMD(Invite, {
	ENSURE_AUTH();
	ENSURE_OP();

	// TODO: actually give permission to join to user

	if (N_PARAMS() != 2)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}
	std::string	invitee = PARAM(0);
	std::string	channelName = PARAM(1);

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

	ITER_CHANNEL_CLIENTS(*channel)
	{
		if (CLIENT()->getNick() == invitee)
		{
			msg.replyError(ERR_USERONCHANNEL, invitee + " "
				+ channelName + " :is already on channel");
			return ;
		}
	}

	IrcClient	*invitedClient = server.getClientByNick(invitee);
	if (invitedClient == NULL)
	{
		msg.replyError(ERR_NOSUCHNICK, ":" + invitee);
		return ;
	}
	client->sendRpl(RPL_INVITING, invitee + " " + channelName);
	invitedClient->sendRaw(
		":" + client->getIdentifier() + " INVITE "
		+ invitee + " " + channelName);
})
