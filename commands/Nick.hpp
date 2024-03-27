/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:46:03 by cgodard          ###   ########.fr       */
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

static bool	isValid(std::string nick)
{
	std::string::const_iterator	it;

	for (it = nick.begin(); it != nick.end(); it++)
		if (!isAllowedCharacter(*it))
			return (false);
	return (true);
}

DEFINE_CMD(Nick, {
	if (N_PARAMS() == 0)
		msg.replyError(ERR_NONICKNAMEGIVEN, ":No nickname given");
	else
	{
		std::string	nick = PARAM(0);

		if (!isValid(nick))
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
		client->setNick(nick);
		if (!client->getUsername().empty())
			client->hasRegistered(server);
	}
})
