/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:42:48 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 22:00:42 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

std::map<int, IrcClient*>	ClientManager::clients;

void		ClientManager::registerClient(SocketTcpClient *client)
{
	clients[client->getFd()] = new IrcClient(client);
}

void		ClientManager::unregisterClient(int fd)
{
	delete clients[fd];
	clients.erase(fd);
}

IrcClient	*ClientManager::getClient(int fd)
{
	return (clients[fd]);
}

void		ClientManager::broadcast(std::string msg)
{
	std::map<int, IrcClient*>::iterator	it;

	for (it = clients.begin(); it != clients.end(); it++)
		it->second->send(msg);
}

bool		ClientManager::isNickInUse(std::string nick)
{
	std::map<int, IrcClient*>::iterator	it;

	for (it = clients.begin(); it != clients.end(); it++)
		if (it->second->getNick() == nick)
			return (true);
	return (false);
}
