/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 18:06:20 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMessage.hpp"

IrcMessage::IrcMessage(void): error(IRC_MESSAGE_NO_ERROR)
{
}

IrcMessage::IrcMessage(IrcMessage const &other):	prefix(other.prefix),
													command(other.command),
													params(other.params),
													error(other.error)
{
}

IrcMessage::~IrcMessage(void)
{
}

IrcMessage::IrcMessage(std::string const &msg): error(IRC_MESSAGE_NO_ERROR)
{
	this->parse(msg);
}

IrcMessageError					IrcMessage::parse(std::string const &msg)
{
	std::stringstream	sMsg(msg);
	
	this->error = IRC_MESSAGE_NO_ERROR;
	if (this->parsePrefix(sMsg) == PARSE_ERROR)
		this->error |= IRC_PREFIX_ERROR;
	if (this->parseCommand(sMsg) == PARSE_ERROR)
		this->error |= IRC_COMMAND_ERROR;
	if (this->parseParams(sMsg) == PARSE_ERROR)
		this->error |= IRC_PREFIX_ERROR;
	return (this->error);
}

IrcMessageError					IrcMessage::getError(void) const
{
	return (this->error);
}

std::string const				&IrcMessage::getPrefix(void) const
{
	return (this->prefix);
}

std::string const				&IrcMessage::getCommand(void) const
{
	return (this->command);
}

std::vector<std::string> const	&IrcMessage::getParams(void) const
{
	return (this->params);
}

IrcMessage	&IrcMessage::operator=(IrcMessage const &other)
{
	this->prefix = other.prefix;
	this->command = other.command;
	this->params = other.params;
	this->error = other.error;
	return (*this);
}
