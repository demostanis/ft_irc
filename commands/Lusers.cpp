/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lusers.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 23:51:50 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lusers.hpp"

void	Lusers::doIt(IrcServer &server, IrcClient *client)
{
	std::string	count;

	kdo::convert(count, server.userCount());
	client->sendRpl(RPL_LUSERCLIENT, "There are " + count + " users on 1 server");
	client->sendRpl(RPL_LUSERME, "I have " + count + " users and 1 server");
}

void	Lusers::handle(IrcServer &server, IrcMessage &msg)
{
	IrcClient		*client = msg.getClient();

	if (client)
	{
		if (!client->isRegistered())
		{
			msg.replyError(ERR_NOTREGISTERED, ":You have not registered");
			return ;
		}
		Lusers::doIt(server, client);
	}
}
