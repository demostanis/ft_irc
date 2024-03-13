/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 13:56:28 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMessage.hpp"

BNFVar	getInitalParser(void)
{
	BNFChar		SPACE("SPACE", ' ');
	BNFChar		cl("cl", ':');
	BNFChar		pt("pt", '.');
	BNFChar		excl("excl", '!');
	BNFChar		hash("hash", '#');
	BNFChar		plus("plus", '+');
	BNFChar		percnt("percnt", '%');
	BNFChar		at("at", '@');
	BNFChar		comma("comma", ',');
	BNFChar		et("and", '&');
	BNFString	crlf("crlf", "\r\n");
	BNFRange	digit("digit", '0', '9');
	BNFRange	minusLetter("minusLetter", 'a', 'z');
	BNFRange	upperLetter("upperLetter", 'A', 'Z');
	BNFAlts		letter("letter", 2, &minusLetter, &upperLetter);
	BNFAlts		hexdigit("hexdigit", digit | 
}

BNFVar const	IrcMessage::initialParser("message", getInitalParser());

IrcMessage::IrcMessage(void):	parser("message", IrcMessage::initialParser),	
								error(IRC_MESSAGE_NO_ERROR)
{
}

IrcMessage::IrcMessage(IrcMessage const &other):	parser("message", other.parser),
													prefix(other.prefix),
													command(other.command),
													params(other.params),
													error(other.error)
{
}

IrcMessage::~IrcMessage(void)
{
}

IrcMessage::IrcMessage(std::string const &msg):	parser("message", IrcMessage::initialParser),
												error(IRC_MESSAGE_NO_ERROR)
{
	this->parse(msg);
}

IrcMessageError					IrcMessage::parse(std::string const &msg)
{
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
