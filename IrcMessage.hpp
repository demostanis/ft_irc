/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/09 17:40:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "kdolib/kdolib.hpp"

#define PARSE_ERROR -1

enum EIrcMessageError
{
	IRC_MESSAGE_NO_ERROR	= 0,
	IRC_PREFIX_ERROR		= 1 << 0, 
	IRC_COMMAND_ERROR		= 1 << 1,
	IRC_PARAMS_ERROR		= 1 << 2
};

typedef uint8_t	IrcMessageError;

class IrcMessage
{
	private:
		std::string					prefix;
		std::string					command;
		std::vector<std::string>	params;	
		IrcMessageError				error;

		ssize_t						parsePrefix(std::stringstream &sMsg);
		ssize_t						parseCommand(std::stringstream &sMsg);
		ssize_t						parseParams(std::stringstream &sMsg);

		static ssize_t				parseNospcrlfcl(std::stringstream sMsg);
		static ssize_t				parseMiddle(std::stringstream sMsg);
		static ssize_t				parseTrailing(std::stringstream sMsg);

		static ssize_t				parseSpace(std::stringstream sMsg);
		static ssize_t				parseCrlf(std::stringstream sMsg);

		static ssize_t				parseTarget(std::stringstream sMsg);
		static ssize_t				parseMsgtarget(std::stringstream sMsg);
		static ssize_t				parseMsgto(std::stringstream sMsg);
		static ssize_t				parseChannel(std::stringstream sMsg);

		static ssize_t				parseServername(std::stringstream sMsg);
		static ssize_t				parseHost(std::stringstream sMsg);
		static ssize_t				parseHostname(std::stringstream sMsg);
		static ssize_t				parseShortname(std::stringstream sMsg);

		static ssize_t				parseHostaddr(std::stringstream sMsg);
		static ssize_t				parseIp4addr(std::stringstream sMsg);
		static ssize_t				parseIp6addr(std::stringstream sMsg);
		static ssize_t				parseNickname(std::stringstream sMsg);
		static ssize_t				parseTargetmask(std::stringstream sMsg);

		static ssize_t				parseChangstring(std::stringstream sMsg);
		static ssize_t				parseChannelid(std::stringstream sMsg);
		static ssize_t				parseUser(std::stringstream sMsg);

		static ssize_t				parseKey(std::stringstream sMsg);
		static ssize_t				parseLetter(std::stringstream sMsg);
		static ssize_t				parseDigit(std::stringstream sMsg);
		static ssize_t				parseHexdigit(std::stringstream sMsg);
		static ssize_t				parseSpecial(std::stringstream sMsg);

		static ssize_t				parseOR(std::stringstream sMsg, t_uint count, ...);
		static ssize_t				parseAND(std::stringstream sMsg, t_uint count, ...);

	public:
										IrcMessage(void);
										IrcMessage(std::string const &msg);
										IrcMessage(IrcMessage const &other);
										~IrcMessage(void);
		IrcMessageError					parse(std::string const &msg);
		IrcMessageError					getError(void) const;
		std::string const				&getPrefix(void) const;
		std::string const				&getCommand(void) const;
		std::vector<std::string> const	&getParams(void) const;
		IrcMessage						&operator=(IrcMessage const &other);
};

typedef size_t (*TIrcParseFunc)(std::stringstream);
