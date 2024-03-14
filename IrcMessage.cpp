/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 02:09:35 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMessage.hpp"

BNFVar	getMessageParser(void)
{
	BNFChar		SPACE("SPACE", ' ');
	BNFChar		zero("zero", '0');
	BNFString	crlf("crlf", "\r\n");
	BNFRange	digit("digit", '0', '9');
	BNFVar		letter("letter", BNFRange('a', 'z') | BNFRange('A', 'Z'));
	BNFVar		hexdigit("hexdigit", digit | BNFRange('A', 'F'));
	BNFVar		special("special", BNFRange(0x5B, 0x60) | BNFRange(0x7B, 0x7D));
	BNFVar		nospcrlfcl("nospcrlfcl", BNFRange(0x01, 0x09) | BNFRange(0x0B, 0X0C)
					| BNFRange(0x0E, 0x1F) | BNFRange(0x21, 0x39) | BNFRange(0x3B, 0xFF));
	BNFVar		user("user", (BNFRange(0x01, 0x09) | BNFRange(0x0B, 0x0C) | BNFRange(0x0E, 0x1F)
					| BNFRange(0x21, 0x3F) | BNFRange(0x41, 0xFF)) - 1);
	BNFVar		nickname("nickname", (letter | special) & (letter | digit | special | '-') + 8);
	BNFVar		ip4addr("ip4addr", digit - 1 + 3 & '.' & digit - 1 + 3
					& '.' & digit - 1 + 3 & '.' & digit - 1 + 3);
	BNFVar		ip6addr("ip6addr", (hexdigit - 1 & (hexdigit - 1 & ':') - 7 + 7)
					| ("0:0:0:0:0:" & (zero | "FFFF") & ':' & ip4addr));
	BNFVar		hostaddr("hostaddr", ip4addr | ip6addr);
	BNFVar		shortname("shortname", (letter | digit) & (letter | digit | '-') - 0
					& (letter | digit) - 0);
	BNFVar		hostname("hostname", shortname & ('.' & shortname) - 0);
	BNFVar		host("host", hostname | hostaddr);
	BNFVar		servername("servername", hostname);
	BNFVar		trailing("trailing", (':' | SPACE | nospcrlfcl) - 0);
	BNFVar		middle("middle", nospcrlfcl & (':' | nospcrlfcl) - 0);
	BNFVar		params("params", ((SPACE & middle) + 14 & (SPACE & ':' & trailing) + 1));
	BNFVar		command("command", letter - 1 | digit - 3 + 3);
	BNFVar		prefix("prefix", servername | (nickname & (('!' & user) + 1 & '@' & host) + 1));
	BNFVar		message("message", (':' & prefix & SPACE) + 1 & command & params + 1 & crlf);

	return (message);
}

BNFVar	IrcMessage::parser(getMessageParser());

IrcMessage::IrcMessage(void):	error(IRC_MESSAGE_NO_ERROR)
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

IrcMessage::IrcMessage(std::string const &msg):	error(IRC_MESSAGE_NO_ERROR)
{
	this->parse(msg);
}

IrcMessageError		IrcMessage::parse(std::string const &msg, size_t start)
{
	this->error = IRC_MESSAGE_NO_ERROR;
	if (IrcMessage::parser.parse(msg, start) == BNF_PARSE_ERROR)
		this->error |= IRC_MESSAGE_ERROR;
	this->prefix = IrcMessage::parser["prefix"];
	if (this->prefix.size() && (this->prefix)[0].getErrorPos() != BNF_ERROR_POS_NONE)
		this->error |= IRC_PREFIX_ERROR;
	this->command = IrcMessage::parser["command"];
	if (this->command.size() && (this->command)[0].getErrorPos() != BNF_ERROR_POS_NONE)
		this->error |= IRC_COMMAND_ERROR;
	this->params = IrcMessage::parser["params"];
	if (this->params.size() && (this->params)[0].getErrorPos() != BNF_ERROR_POS_NONE)
		this->error |= IRC_PARAMS_ERROR;
	this->params = IrcMessage::parser["middle"].isSuccess();
	this->params.merge(IrcMessage::parser["trailing"].isSuccess());
	return (this->error);
}

IrcMessageError		IrcMessage::getError(void) const
{
	return (this->error);
}

BNFFind const		&IrcMessage::getPrefix(void) const
{
	return (this->prefix);
}

BNFFind const		&IrcMessage::getCommand(void) const
{
	return (this->command);
}

BNFFind const		&IrcMessage::getParams(void) const
{
	return (this->params);
}

IrcMessage			&IrcMessage::operator=(IrcMessage const &other)
{
	this->prefix = other.prefix;
	this->command = other.command;
	this->params = other.params;
	this->error = other.error;
	return (*this);
}
