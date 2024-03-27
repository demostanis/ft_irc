/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:10:30 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Pass, {
	if (N_PARAMS() == 0)
		msg.replyError(ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
	else
	{
		std::string	password = PARAM(0);
		IrcClient	*client	= msg.getClient();

		// TODO: should be argv[1] instead of config.password
		if (password == server.getConfig()["password"])
		{
			if (client)
			{
				if (client->getHasGivenPassword())
					msg.replyError(ERR_ALREADYREGISTERED, ":You may not reregister");
				else
					client->setHasGivenPassword();
			}
		}
		else
			msg.replyError(ERR_PASSWDMISMATCH, ":Password incorrect");
	}
})
