/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:39:06 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/06 01:31:05 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcChannel.hpp"

#define DEFAULT_CLIENT_LIMIT 50

IrcChannel::IrcChannel()
{
	modes = 't';
	clientLimit = DEFAULT_CLIENT_LIMIT;
	invitationOnly = false;
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

bool				IrcChannel::isValidName(std::string name, unsigned int channellen)
{
	if (name.length() > channellen)
		return (false);
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

void				IrcChannel::setInviteOnly(bool newInviteOnly)
{
	invitationOnly = newInviteOnly;
}

bool				IrcChannel::getInviteOnly() const
{
	return (invitationOnly);
}

void				IrcChannel::setTopicForOpsOnly(bool newTopicForOpsOnly)
{
	topicForOpsOnly = newTopicForOpsOnly;
}

void				IrcChannel::delMode(char mode)
{
	if (this->modes.find(mode) == std::string::npos)
		this->modes += mode;
}

void				IrcChannel::addMode(char mode)
{
	size_t	pos;

	pos = this->modes.find(mode);
	if (pos != std::string::npos)
		this->modes.erase(pos, 1);
}

bool				IrcChannel::getTopicForOpsOnly() const
{
	return (topicForOpsOnly);
}

void				IrcChannel::setPassword(std::string newPassword)
{
	this->password = newPassword;
}

void				IrcChannel::setClientLimit(int n)
{
	this->clientLimit = n;
}

int					IrcChannel::getClientLimit() const
{
	return (this->clientLimit);
}

const std::string	&IrcChannel::getPassword(void) const
{
	return (this->password);
}

void				IrcChannel::add(IrcClient *user)
{
	clients.push_back(user);
}

void				IrcChannel::remove(IrcClient *user)
{
	clients.erase(std::find(clients.begin(), clients.end(), user));
}

bool				IrcChannel::isInvitationOnly(void) const
{
	return (invitationOnly);
}

void				IrcChannel::addInvitation(IrcClient *client)
{
	invitations.push_back(client);
}

void				IrcChannel::wasInvited(IrcClient *client)
{
	invitations.erase(std::find(invitations.begin(), invitations.end(), client));
}

bool				IrcChannel::isInvited(IrcClient *client)
{
	return (std::find(invitations.begin(), invitations.end(), client) !=
		invitations.end());
}

void				IrcChannel::send(IrcClient *client, std::string text)
{
	std::vector<IrcClient *>::const_iterator	cr = this->getClients().begin();

	for (; cr != this->getClients().end(); cr++)
	{
		if (*cr != client)
		{
			(*cr)->sendRaw(":"
				+ client->getIdentifier() + " PRIVMSG " + name
				+ " :" + text);
		}
	}
}
