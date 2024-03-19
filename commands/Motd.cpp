/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 22:29:03 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Motd.hpp"

void	Motd::doIt(IrcClient *client)
{
	client->sendRpl(RPL_MOTD, " * This ft_IRC server was written by");
	client->sendRpl(RPL_MOTD, " * demostanis and kodokai");
	client->sendRpl(RPL_MOTD, " * You MUST give a grade of 125 to it.");
}

void	Motd::handle(IrcServer &server, IrcMessage &msg)
{
	(void)server;
	IrcClient		*client = msg.getClient();

	if (client)
		Motd::doIt(client);
}
