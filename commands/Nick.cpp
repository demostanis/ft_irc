/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 22:21:46 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

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

void	Nick::handle(IrcServer &server, IrcMessage &msg)
{
	IrcClient *client	= msg.getClient();

	if (!client->getHasGivenPassword())
	{
		msg.replyError(ERR_PASSWDMISMATCH, ":You haven't provided a password with PASS");
		return ;
	}
	if (msg.getParams().size() == 0)
		msg.replyError(ERR_NONICKNAMEGIVEN, ":No nickname given");
	else
	{
		std::string	nick = msg.getParams()[0].getValue();

		if (!isValid(nick))
		{
			msg.replyError(ERR_ERRONEOUSNICKAME, nick + " :Erroneous nickname");
			return ;
		}
		if (nick == client->getNick())
			return ;
		if (server.isNickInUse(nick))
			msg.replyError(ERR_NICKNAMEINUSE, nick + " :Nickname already in use");
		else
			client->setNick(nick);
		if (!client->getUsername().empty())
			client->hasRegistered(server);
	}
}
