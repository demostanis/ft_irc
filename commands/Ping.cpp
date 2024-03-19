/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 19:39:08 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

void	Ping::handle(IrcServer &server, IrcMessage &msg)
{
	if (msg.getParams().size() == 0)
		msg.replyError(ERR_NEEDMOREPARAMS, "PING :Not enough parameters");
	else
		msg.reply("PONG " + server.getConfig()["source"] + " :" + msg.getParams()[0].getValue());
}
