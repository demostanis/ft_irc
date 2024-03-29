/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:07:59 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 21:34:03 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"

enum
{
	RPL_WELCOME = 1,
	RPL_YOURHOST = 2,
	RPL_CREATED = 3,
	RPL_MYINFO = 4,
	RPL_ISUPPORT = 5
};

IrcClient::IrcClient(Config &config):	config(config),
										registered(false),
										hasGivenPassword(false)
{
}

IrcClient::IrcClient(Config &config, int socketConnected):	SocketTcpClient(socketConnected),
															config(config),
															registered(false),
															hasGivenPassword(false)
{
}

IrcClient::~IrcClient(void)
{
}

bool	IrcClient::isRegistered(void) const
{
	return (this->registered);
}

void	IrcClient::sendRaw(std::string msg) const
{
	this->send(msg + CRLF, MSG_DONTWAIT);
}

void	IrcClient::sendRpl(int rpl, std::string msg) const
{
	std::string	code = kdo::itoa(rpl);

	code.insert(code.begin(), 3 - code.size(), '0');
	this->sendRaw(
		":" + this->config["source"] + " " + code
		+ " " + this->getNick() + " " + msg);
}

void	IrcClient::hasRegistered(IrcServer &server)
{
	// TODO: get real IP
	this->identifier = nick + "!~" + nick + "@127.0.0.1";

	this->registered = true;
	this->sendRpl(RPL_WELCOME,
		"Welcome to " + this->config["source"] + ", " + this->nick + "!");
	this->sendRpl(RPL_YOURHOST,
		"Your host is " + this->config["source"] + ", running version 0.42.69");
	this->sendRpl(RPL_CREATED,
		"This server was created on 1st January 1970");
	this->sendRpl(RPL_MYINFO,
		this->config["source"] + " 0.42.69 o itkol");
	this->sendRpl(RPL_ISUPPORT, std::string("CASEMAPPING=ascii CHANMODES=itkol USERMODES=o")
		+ " CHANLIMIT=#:" + this->config["chanlimit"]
		// TODO: check
		+ " CHANNELLEN=" + this->config["channellen"]
		+ " NETWORK=" + this->config["source"]
		// TODO: check
		+ " NICKLEN=" + this->config["nicklen"]);
	lusers(server, this);
	motd(this);
}

bool	IrcClient::getHasGivenPassword(void) const
{
	return (this->hasGivenPassword);
}

void	IrcClient::setHasGivenPassword(void)
{
	hasGivenPassword = true;
}

void	IrcClient::setNick(const std::string &nick)
{
	this->nick = nick;
}

const std::string	&IrcClient::getNick() const
{
	return (this->nick);
}

const std::string	&IrcClient::getModes() const
{
	return (this->modes);
}

void				IrcClient::addMode(char mode)
{
	if (this->modes.find(mode) == std::string::npos)
		this->modes += mode;
}

void				IrcClient::delMode(char mode)
{
	size_t	pos;

	pos = this->modes.find(mode);
	if (pos != std::string::npos)
		this->modes.erase(pos, 1);
}

const std::string	&IrcClient::getUsername() const
{
	return (this->username);
}

const std::string	&IrcClient::getRealname() const
{
	return (this->realname);
}

const std::string	&IrcClient::getIdentifier() const
{
	return (this->identifier);
}

void				IrcClient::setIdentity(const std::string &username, const std::string &realname)
{
	this->username = username;
	this->realname = realname;
}

Config				&IrcClient::getConfig(void)
{
	return (this->config);
}

const std::map<std::string, IrcChannel*>	&IrcClient::getChannels() const
{
	return (this->channels);
}

void	IrcClient::addChannel(IrcChannel *channel)
{
	this->channels[channel->getName()] = channel;
}

void	IrcClient::removeChannel(IrcChannel *channel)
{
	this->channels[channel->getName()] = NULL;
}

bool	IrcClient::isInChannel(IrcChannel *channel)
{
	std::vector<IrcClient *>::const_iterator	clients;

	clients = channel->getClients().begin();
	for (; clients != channel->getClients().end(); ++clients)
		if (*clients == this)
			return (true);
	return (false);
}
