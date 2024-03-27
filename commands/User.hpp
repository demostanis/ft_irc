/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:52:21 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(User, {
	IrcClient	*client	= msg.getClient();

	if (!client->getHasGivenPassword())
	{
		msg.replyError(ERR_PASSWDMISMATCH, ":You haven't provided a password with PASS");
		return ;
	}
	if (client->isRegistered())
	{
		msg.replyError(ERR_ALREADYREGISTERED, ":You may not reregister");
		return ;
	}
	if (N_PARAMS() < 4 || PARAM(0) == "")
		msg.replyError(ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
	else
	{
		size_t		len = msg.getParams().size();
		std::string	username = PARAM(0);
		std::string	realname;

		// 2nd and 3rd params are ignored
		for (size_t	i = 3; i < len; i++)
		{
			realname += PARAM(i);
			if (i != len - 1)
				realname += " ";
		}
		client->setIdentity(username, realname);
		if (!client->getNick().empty())
			client->hasRegistered(server);
	}
})
