/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/18 13:24:11 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Privmsg, {
	ENSURE_AUTH();

	if (N_PARAMS() == 0)
	{	
		msg.replyError(ERR_NORECIPIENT, ":No recipient given");
		return ;
	}
	if (N_PARAMS() == 1)
	{
		msg.replyError(ERR_NOTEXTTOSEND, ":No text to send");
		return ;
	}

	std::string		targetsRaw = PARAM(0);
	BNFFind			targets;

	listParser.parse(targetsRaw);
	targets = listParser["word"];

	unsigned int	chanlimit;
	kdo::convert(chanlimit, server.getConfig()["chanlimit"]);
	if (client->getChannels().size() + targets.size() >= chanlimit)
	{
		msg.replyError(ERR_TOOMANYTARGETS, ":Too many targets");
		return ;
	}

	BNFFind::iterator	cr = targets.begin();
	for (; cr != targets.end(); ++cr)
	{
		if ((*cr)[0] == '#')
		{
			IrcChannel	*channel = server.getChannel(cr->string());
			if (!client->isInChannel(channel))
			{
				msg.replyError(ERR_CANNOTSENDTOCHAN, ":Cannot send to channel");
				return ;
			}
			if (channel)
				channel->send(client, PARAM(1));
			else
				msg.replyError(ERR_NOSUCHNICK, ":No such nick/channel");
		}
		else
		{
			IrcClient	*targetClient = server.getClientByNick(cr->string());
			if (targetClient == client || targetClient == NULL)
			{
				msg.replyError(ERR_NOSUCHNICK, ":No such nick/channel");
				return ;
			}
			targetClient->sendRaw(":" + client->getIdentifier() + " PRIVMSG " +
				*cr + " :" + PARAM(1));
		}
	}
})
