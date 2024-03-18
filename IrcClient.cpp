/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:07:59 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/18 01:14:54 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"
#include "Config.hpp"

extern Config	config;

enum
{
	RPL_WELCOME = 1,
	RPL_YOURHOST = 2,
	RPL_CREATED = 3,
	RPL_MYINFO = 4
};

IrcClient::IrcClient(void): registered(false),
							hasGivenPassword(false)
{
}

IrcClient::IrcClient(int socketConnected): SocketTcpClient(socketConnected),
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

void	IrcClient::sendRpl(int rpl, std::string msg) const
{
	std::string	code = kdo::itoa(rpl);

	code.insert(code.begin(), 3 - code.size(), '0');
	this->send(
		":" + config.prefix + " " + code
		+ " " + this->getNick() + " " + msg + "\r\n");
}

void	IrcClient::hasRegistered(void)
{
	this->registered = true;
	this->sendRpl(RPL_WELCOME,
		"Welcome to " + config.prefix + ", " + this->nick + "!");
	this->sendRpl(RPL_YOURHOST,
		"Your host is " + config.prefix + ", running version 0.42.69");
	this->sendRpl(RPL_CREATED,
		"This server was created on 1st January 1970");
	this->sendRpl(RPL_MYINFO,
		config.prefix + " 0.42.69  itkol");
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

void				IrcClient::setIdentity(const std::string &username, const std::string &realname)
{
	this->username = username;
	this->realname = realname;
}
