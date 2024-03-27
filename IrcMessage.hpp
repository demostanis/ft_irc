/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/27 11:45:47 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

#define CRLF "\r\n"

enum EIrcMessageError
{
	IRC_MESSAGE_NO_ERROR	= 0,
	IRC_MESSAGE_ERROR		= 1 << 0,
	IRC_SOURCE_ERROR		= 1 << 1, 
	IRC_COMMAND_ERROR		= 1 << 2,
	IRC_PARAMS_ERROR		= 1 << 3
};

enum ReplyError
{
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NEEDMOREPARAMS = 461,
	ERR_PASSWDMISMATCH = 464,
	ERR_ALREADYREGISTERED = 462,
	ERR_NOTREGISTERED = 451,
	ERR_NICKNAMEINUSE = 433,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEOUSNICKAME = 432,
	ERR_BADCHANNAME = 479,
	ERR_USERSDONTMATCH = 502,
	ERR_NOSUCHCHANNEL = 403,
	ERR_NORECIPIENT = 411,
	ERR_NOTEXTTOSEND = 412,
	ERR_NOSUCHNICK = 401,
	ERR_TOOMANYTARGETS = 407,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_NOTONCHANNEL = 442,
};

typedef uint8_t	IrcMessageError;

class IrcClient;

class IrcMessage
{
	private:
		static BNFVar	parser;
		BNFFind			source;
		BNFFind			command;
		BNFFind			params;	
		IrcMessageError	error;
		IrcClient		*client;

	public:
							IrcMessage(IrcClient *client = NULL);
							IrcMessage(std::string const &msg, IrcClient *client);
							IrcMessage(IrcMessage const &other);
							~IrcMessage(void);
		IrcMessageError		parse(std::string const &msg, size_t start = 0);
		IrcMessageError		getError(void) const;
		BNFFind	const		&getPrefix(void) const;
		BNFFind const		&getCommand(void) const;
		BNFFind const		&getParams(void) const;
		IrcClient			*getClient(void) const;
		void				setClient(IrcClient *client);
		ssize_t				reply(std::string const &reply) const;
		ssize_t				replyError(int code, std::string const &reply) const;
		IrcMessage			&operator=(IrcMessage const &other);
};
