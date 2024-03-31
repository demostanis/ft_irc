/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/31 20:10:54 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

static bool	isAllowedCharacter(char c)
{
	return (c == '[' || c == ']' || c == '{' || c == '}' || c == '_'
			|| c == '\\' || c == '|' || (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

static bool	isValid(std::string nick, unsigned int nicklen)
{
	std::string::const_iterator	it;

	if (nick.length() > nicklen)
		return (false);
	for (it = nick.begin(); it != nick.end(); it++)
		if (!isAllowedCharacter(*it))
			return (false);
	return (true);
}

DEFINE_CMD(Nick, {
	unsigned int	nicklen;
	kdo::convert(nicklen, server.getConfig()["nicklen"]);

	if (N_PARAMS() == 0)
		msg.replyError(ERR_NONICKNAMEGIVEN, ":No nickname given");
	else
	{
		std::string	nick = PARAM(0);

		if (!isValid(nick, nicklen))
		{
			msg.replyError(ERR_ERRONEOUSNICKAME, nick + " :Erroneous nickname");
			return ;
		}
		if (nick == client->getNick())
			return ;
		if (server.isNickInUse(nick))
		{
			msg.replyError(ERR_NICKNAMEINUSE, nick + " :Nickname already in use");
			return ;
		}
		if (!client->isRegistered())
		{
			client->setNick(nick);
			if (!client->getUsername().empty())
				client->hasRegistered(server);
		}
		else
		{
			client->sendRaw(":" + client->getIdentifier() + " NICK :" + nick);
			client->setNick(nick);
		}
	}
})
