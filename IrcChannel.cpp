/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:39:06 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 11:47:22 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcChannel.hpp"

IrcChannel::IrcChannel()
{
}

IrcChannel::~IrcChannel()
{
}

const std::string	&IrcChannel::getName(void) const
{
	return (name);
}

const std::vector<IrcClient *>	&IrcChannel::getClients(void) const
{
	return (clients);
}

bool				IrcChannel::isValidName(std::string name)
{
	if (name.length() < 2)
		return (false);
	if (name[0] != '#')
		return (false);
	for (size_t i = 1; i < name.length(); i++)
		if (i == 7 /* ^G */ || i == ' ' || i == ',')
			return (false);
	return (true);
}

void				IrcChannel::setName(std::string newName)
{
	name = newName;
}

const std::string	&IrcChannel::getTopic(void) const
{
	return (topic);
}

const std::string	&IrcChannel::getModes(void) const
{
	return (modes);
}

void				IrcChannel::setTopic(std::string newTopic)
{
	topic = newTopic;
}

void				IrcChannel::add(IrcClient *user)
{
	clients.push_back(user);
}

void				IrcChannel::remove(IrcClient *user)
{
	clients.erase(std::find(clients.begin(), clients.end(), user));
}

void				IrcChannel::send(IrcClient *client, std::string text)
{
	std::vector<IrcClient *>::const_iterator	cr = this->getClients().begin();

	for (; cr != this->getClients().end(); cr++)
	{
		if (*cr != client)
		{
			(*cr)->sendRaw(":"
				+ client->getNick() + " PRIVMSG " + name
				+ " :" + text);
		}
	}
}
