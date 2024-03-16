/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 23:07:58 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/User.hpp"

void	User::handle(IrcMessage &msg)
{
	IrcClient	*client	= msg.getClient();

	if (!client->getHasGivenPassword())
	{
		msg.replyError(ERR_PASSWDMISMATCH, ":You haven't provided a password with PASS");
		return ;
	}
	if (!client->getHasGivenPassword())
	{
		msg.replyError(ERR_NOTREGISTERED, ":You need to set a nickname with NICK first");
		return ;
	}
	if (client->isRegistered())
	{
		msg.replyError(ERR_ALREADYREGISTERED, ":You may not reregister");
		return ;
	}
	if (msg.getParams().size() < 4 || msg.getParams()[0].getValue() == "")
		msg.replyError(ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
	else
	{
		size_t		len = msg.getParams().size();
		std::string	username = msg.getParams()[0].getValue();
		std::string	realname;

		// 2nd and 3rd params are ignored
		for (size_t	i = 3; i < len; i++)
		{
			realname += msg.getParams()[i].getValue();
			if (i != len - 1)
				realname += " ";
		}
		client->setIdentity(username, realname);
		client->hasRegistered();
	}
}
