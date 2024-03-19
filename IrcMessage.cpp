/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 21:18:25 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMessage.hpp"

static BNFVar	_messageParser(void)
{
	BNFChar		SPACE("SPACE", ' ');
	BNFChar		zero("zero", '0');
	BNFChar		client_source("client_source", '+');
	BNFStr		crlf("crlf", CRLF);
	BNFRange	digit("digit", '0', '9');
	BNFVar		letter("letter", BNFRange('a', 'z') | BNFRange('A', 'Z'));
	BNFVar		hexdigit("hexdigit", digit | BNFRange('A', 'F'));
	BNFVar		special("special", BNFRange(0x5B, 0x60) | BNFRange(0x7B, 0x7D));
	BNFVar		nospcrlfcl("nospcrlfcl", BNFRange(0x01, 0x09) | BNFRange(0x0B, 0X0C)
					| BNFRange(0x0E, 0x1F) | BNFRange(0x21, 0x39) | BNFRange(0x3B, 0xFF));
	BNFVar		user("user", (BNFRange(0x01, 0x09) | BNFRange(0x0B, 0x0C) | BNFRange(0x0E, 0x1F)
					| BNFRange(0x21, 0x3F) | BNFRange(0x41, 0xFF)) - 1);
	BNFVar		escaped_value("escaped_value", BNFRange(0x01, 0x09) | BNFRange(0x0B, 0X0C)
					| BNFRange(0x0E, 0x1F) | BNFRange(0x21, 0x3A) | BNFRange(0x3C, 0xFF));
	BNFVar		nickname("nickname", (letter | special) & (letter | digit | special | '-') + 8);
	BNFVar		ip4addr("ip4addr", digit - 1 + 3 & ('.' & digit - 1 + 3) % 3);
	BNFVar		ip6addr("ip6addr", (hexdigit - 1 & ( ':' & hexdigit - 1) % 7)
					| ("0:0:0:0:0:" & (zero | "FFFF") & ':' & ip4addr));
	BNFVar		hostaddr("hostaddr", ip4addr | ip6addr);
	BNFVar		shortname("shortname", (letter | digit) & (letter | digit | '-') - 0
					& (letter | digit) - 0);
	BNFVar		hostname("hostname", shortname & ('.' & shortname) - 0);
	BNFVar		host("host", hostname | hostaddr);
	BNFVar		servername("servername", hostname);
	BNFVar		vendor("vendor", host);
	BNFVar		key("key", !(client_source) & !(vendor & '/') & (letter | digit) - 0);
	BNFVar		tag("tag", key & !('=' & escaped_value));
	BNFVar		tags("tags", tag & (';' & tag) - 0);
	BNFVar		source("source", servername | (nickname & !('!' & user) & !('@' & host)));
	BNFVar		command("command", letter - 1 | digit % 3);
	BNFVar		middle("middle", nospcrlfcl & (':' | nospcrlfcl) - 0);
	BNFVar		trailing("trailing", (':' | SPACE | nospcrlfcl) - 0);
	BNFVar		parameters("parameters", (SPACE & middle) - 0 & !(SPACE & ':' & trailing));
	BNFVar		message("message", !('@' & tags & SPACE) & !(':' & source & SPACE) & command & !parameters & crlf);

	return (message);
}

BNFVar	IrcMessage::parser(_messageParser());


IrcMessage::IrcMessage(IrcClient *client):	error(IRC_MESSAGE_NO_ERROR),
											client(client)
{
}

IrcMessage::IrcMessage(std::string const &msg, IrcClient *client):	error(IRC_MESSAGE_NO_ERROR),
																	client(client)
{
	this->parse(msg);
}

IrcMessage::IrcMessage(IrcMessage const &other):	source(other.source),
													command(other.command),
													params(other.params),
													error(other.error),
													client(other.client)
{
}

IrcMessage::~IrcMessage(void)
{
}

IrcMessageError		IrcMessage::parse(std::string const &msg, size_t start)
{
	this->error = IRC_MESSAGE_NO_ERROR;
	if (IrcMessage::parser.parse(msg, start) == BNF_PARSE_ERROR)
		this->error |= IRC_MESSAGE_ERROR;
	this->source = IrcMessage::parser.find("source", 5);
	if (this->source.size() && (this->source)[0].getErrorLen() != BNF_ERROR_LEN_NONE)
		this->error |= IRC_SOURCE_ERROR;
	this->command = IrcMessage::parser.find("command", 3);
	if (this->command.size() && (this->command)[0].getErrorLen() != BNF_ERROR_LEN_NONE)
		this->error |= IRC_COMMAND_ERROR;
	this->params = IrcMessage::parser.find("parameters", 3);
	if (this->params.size() && (this->params)[0].getErrorLen() != BNF_ERROR_LEN_NONE)
		this->error |= IRC_PARAMS_ERROR;
	this->params = IrcMessage::parser.find("middle", 8);
	this->params.merge(IrcMessage::parser.find("trailing", 8));
	return (this->error);
}

IrcMessageError		IrcMessage::getError(void) const
{
	return (this->error);
}

BNFFind const		&IrcMessage::getPrefix(void) const
{
	return (this->source);
}

BNFFind const		&IrcMessage::getCommand(void) const
{
	return (this->command);
}

BNFFind const		&IrcMessage::getParams(void) const
{
	return (this->params);
}

IrcClient			*IrcMessage::getClient(void) const
{
	return (this->client);
}

void				IrcMessage::setClient(IrcClient *client)
{
	this->client = client;
}

ssize_t				IrcMessage::reply(std::string const &reply) const
{
	return (this->client->send(":" + this->client->getConfig()["source"] + " " + reply + CRLF), MSG_DONTWAIT);
}

ssize_t				IrcMessage::replyError(int code, std::string const &reply) const
{
	return (this->reply(kdo::itoa(code) + " * " + reply));
}

IrcMessage			&IrcMessage::operator=(IrcMessage const &other)
{
	this->source = other.source;
	this->command = other.command;
	this->params = other.params;
	this->error = other.error;
	this->client = other.client;
	return (*this);
}
