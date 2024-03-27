/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:10:25 by cgodard          ###   ########.fr       */
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

	IrcClient	*client = msg.getClient();

	// TODO: handle setting modes
	std::string	param = PARAM(0);
	if (param[0] == '#')
	{
		if (server.channelExists(param))
			client->sendRpl(RPL_UMODEIS, "+" +
				server.getChannel(param)->getModes());
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
	}
})
