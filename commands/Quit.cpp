/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/21 02:10:09 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"

void	Quit::doIt(IrcClient *client, std::string reason)
{
	std::map<std::string, IrcChannel*>::const_iterator	channels;
	std::vector<IrcClient *>::const_iterator			clients;
	IrcChannel											*channel;

	channels = client->getChannels().begin();
	for (; channels != client->getChannels().end(); ++channels)
	{
		channel = channels->second;
		clients = channel->getClients().begin();
		for (; clients != channel->getClients().end(); ++clients)
			(*clients)->send(":" + client->getNick() +
				" QUIT :" + reason + CRLF, MSG_DONTWAIT);
	}
	// TODO: this doesnt work?
	client->disconnect();
}

void	Quit::handle(IrcServer &server, IrcMessage &msg)
{
	(void)server;
	IrcClient		*client = msg.getClient();
	std::string		reason;

	if (client)
	{
		if (msg.getParams().size() > 0)
			reason = msg.getParams()[0].getValue();
		Quit::doIt(client, reason);
	}
}
