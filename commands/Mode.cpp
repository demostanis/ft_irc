/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/20 22:52:16 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

void	Mode::handle(IrcServer &server, IrcMessage &msg)
{
	IrcClient	*client	= msg.getClient();

	(void)server;
	if (!client || !client->isRegistered())
	{
		msg.replyError(ERR_NOTREGISTERED, ":You have not registered");
		return ;
	}
	if (msg.getParams().size() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}
	if (msg.getParams()[0].getValue()[0] == '#')
	{
		std::string	channelName = msg.getParams()[0].getValue();
		if (server.channelExists(channelName))
			client->sendRpl(RPL_UMODEIS, "+" +
				server.getChannel(channelName)->getModes());
		else
			msg.replyError(ERR_NOSUCHCHANNEL, ":No such channel");
	}
	else
	{
		if (client->getNick() != msg.getParams()[0].getValue())
		{
			msg.replyError(ERR_USERSDONTMATCH, ":Can't change mode for other users");
			return ;
		}
		if (msg.getParams().size() == 1)
			client->sendRpl(RPL_UMODEIS, "+" + client->getModes());
	}
}
