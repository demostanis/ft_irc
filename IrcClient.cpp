/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:07:59 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 17:16:15 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"

enum
{
	RPL_WELCOME = 1,
	RPL_YOURHOST = 2,
	RPL_CREATED = 3,
	RPL_MYINFO = 4
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

void	IrcClient::sendRpl(int rpl, std::string msg) const
{
	std::string	code = kdo::itoa(rpl);

	code.insert(code.begin(), 3 - code.size(), '0');
	this->send(
		":" + this->config["source"] + " " + code
		+ " " + this->getNick() + " " + msg + "\r\n");
}

void	IrcClient::hasRegistered(void)
{
	this->registered = true;
	this->sendRpl(RPL_WELCOME,
		"Welcome to " + this->config["source"] + ", " + this->nick + "!");
	this->sendRpl(RPL_YOURHOST,
		"Your host is " + this->config["source"] + ", running version 0.42.69");
	this->sendRpl(RPL_CREATED,
		"This server was created on 1st January 1970");
	this->sendRpl(RPL_MYINFO,
		this->config["source"] + " 0.42.69  itkol");
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

Config				&IrcClient::getConfig(void)
{
	return (this->config);
}
