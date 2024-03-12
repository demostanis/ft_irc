/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/09 18:05:39 by nlaerema         ###   ########.fr       */
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

ssize_t						IrcMessage::parsePrefix(std::stringstream &sMsg)
{
}

ssize_t						IrcMessage::parseCommand(std::stringstream &sMsg)
{
}

ssize_t						IrcMessage::parseParams(std::stringstream &sMsg)
{
}

ssize_t						IrcMessage::parseNospcrlfcl(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseMiddle(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseTrailing(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseSpace(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseCrlf(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseTarget(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseMsgtarget(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseMsgto(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseChannel(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseServername(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseHost(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseHostname(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseShortname(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseHostaddr(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseIp4addr(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseIp6addr(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseNickname(std::stringstream sMsg)
{
}

ssize_t						IrcMessage::parseTargetmask(std::stringstream sMsg)
{
	char	c(sMsg.get());

	if (c == '$' || c == '#')
		return (IrcMessage::parseM
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseChangstring(std::stringstream sMsg)
{
	char	c(sMsg.get());

	if ((0x01 <= c && c <= 0x07) || (0x08 <= c && c <= 0x09)
		|| (0x0B <= c && c <= 0x0C) || (0x0E <= c && c <= 0x1F)
		|| (0x21 <= c && c <= 0x2B) || (0x2D <= c && c <= 0x39) || 0x3B <= c)
		return (1);
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseChannelid(std::stringstream sMsg)
{
	size_t	parseCount;
	char	c;

	for (parseCount = 0; parseCount < 5; parseCount++)
	{
		c = sMsg.get();
		if (!('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'))
			return (PARSE_ERROR);
	}
	return (parseCount);
}

ssize_t						IrcMessage::parseUser(std::stringstream sMsg)
{
	char	c(sMsg.get());
	size_t	parseCount;

	c = sMsg.get();
	if ((0x01 <= c && c <= 0x09) || (0x0B <= c && c <= 0x0C)
		|| (0x0E <= c && c <= 0x1F) || (0x21 <= c && c <= 0x3F) || 0x41 <= c)
	{
		for (parseCount = 1; parseCount < SSIZE_MAX; parseCount++)
		{
			c = sMsg.get();
			if (!((0x01 <= c && c <= 0x09) || (0x0B <= c && c <= 0x0C)
				|| (0x0E <= c && c <= 0x1F) || (0x21 <= c && c <= 0x3F) || 0x41 <= c))
				break;
		}
		return (parseCount);
	}
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseKey(std::stringstream sMsg)
{
	char	c(sMsg.get());
	size_t	parseCount;

	c = sMsg.get();
	if ((0x01 <= c && c <= 0x05) || (0x07 <= c && c <= 0x08)
		|| c == 0x0C || (0x0E <= c && c <= 0x1F) || (0x21 <= c || 0x7F <= c))
	{
		for (parseCount = 1; parseCount < 23; parseCount++)
		{
			c = sMsg.get();
			if (!((0x01 <= c && c <= 0x05) || (0x07 <= c && c <= 0x08)
				|| c == 0x0C || (0x0E <= c && c <= 0x1F) || (0x21 <= c || 0x7F <= c)))
				break;
		}
		return (parseCount);
	}
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseLetter(std::stringstream sMsg)
{
	char	c(sMsg.get());

	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseDigit(std::stringstream sMsg)
{
	char	c(sMsg.get());

	if ('0' <= c && c <= '9')
		return (1);
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseHexdigit(std::stringstream sMsg)
{
	char	c(sMsg.get());

	if (('0' <= c && c <= '9') || ('A' <= c && c <= 'F'))
		return (1);
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseSpecial(std::stringstream sMsg)
{
	char	c(sMsg.get());

	if ((0x5B <= c && c <= 0x60) || (0x7B <= c && c <= 0x7D))
		return (1);
	return (PARSE_ERROR);
}

ssize_t						IrcMessage::parseOR(std::stringstream sMsg, t_uint count, ...)
{
	va_list				argList;
	ssize_t				maxParseCount;
	ssize_t				parseCount;
	TIrcParseFunc		parseFunc;

	parseCount = PARSE_ERROR;
	va_start(argList, count);
	for (t_uint i = 0; i < count; i++)
	{
		parseFunc = va_arg(argList, TIrcParseFunc);
		parseCount = (*parseFunc)(sMsg);
		maxParseCount = std::max(maxParseCount, parseCount);
	}
	va_end(argList);
	return (maxParseCount);
}

ssize_t						IrcMessage::parseAND(std::stringstream sMsg, t_uint count, ...)
{
	va_list				argList;
	ssize_t				allParseCount;
	ssize_t				parseCount;
	TIrcParseFunc		parseFunc;

	parseCount = 0;
	va_start(argList, count);
	for (t_uint i = 0; i < count; i++)
	{
		parseFunc = va_arg(argList, TIrcParseFunc);
		parseCount = (*parseFunc)(sMsg);
		if (parseCount == PARSE_ERROR)
			return (va_end(argList), PARSE_ERROR);
		allParseCount += parseCount;
	}
	va_end(argList);
	return (allParseCount);
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
