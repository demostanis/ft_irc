/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:07:59 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 23:33:08 by cgodard          ###   ########.fr       */
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

		IrcClient::IrcClient(): SocketTcpClient(),
								registered(false),
								hasGivenPassword(false),
								nick(""),
								username(""),
								realname("")
{
}

		IrcClient::IrcClient(SocketTcpClient *client): SocketTcpClient(client->getFd()),
													   registered(false),
													   hasGivenPassword(false),
													   nick(""),
													   username(""),
													   realname("")
{
}

		IrcClient::~IrcClient()
{
}

bool	IrcClient::isRegistered(void) const
{
	return (registered);
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
	registered = true;
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
	return (hasGivenPassword);
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
