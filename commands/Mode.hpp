/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 20:37:15 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Mode, {
	ENSURE_AUTH();

	if (N_PARAMS() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	std::string	param = PARAM(0);
	if (param[0] == '#')
	{
		if (server.channelExists(param))
		{
			if (N_PARAMS() == 1)
				client->sendRpl(RPL_UMODEIS, "+" +
					server.getChannel(param)->getModes());
			else
			{
			}
		}
		else
			msg.replyError(ERR_NOSUCHCHANNEL, ":No such channel");
	}
	else
	{
		if (client->getNick() != param)
		{
			msg.replyError(ERR_USERSDONTMATCH, ":Can't change mode for other users");
			return ;
		}
		if (N_PARAMS() == 1)
			client->sendRpl(RPL_UMODEIS, "+" + client->getModes());
		else
		{
			if (PARAM(1).find('o') != std::string::npos)
			{
				if (PARAM(1)[0] == '+')
					client->addMode('o');
				else if (PARAM(1)[0] == '-')
					client->delMode('o');
			}
		}
	}
})
