/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 01:19:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "BNF/BNF.hpp"
#include "kdolib/kdolib.hpp"

#define PARSE_ERROR -1

enum EIrcMessageError
{
	IRC_MESSAGE_NO_ERROR	= 0,
	IRC_MESSAGE_ERROR		= 1 << 0,
	IRC_PREFIX_ERROR		= 1 << 1, 
	IRC_COMMAND_ERROR		= 1 << 2,
	IRC_PARAMS_ERROR		= 1 << 3
};

typedef uint8_t	IrcMessageError;

class IrcMessage
{
	private:
		static BNFVar	parser;
		BNFFind			prefix;
		BNFFind			command;
		BNFFind			params;	
		IrcMessageError	error;

	public:
							IrcMessage(void);
							IrcMessage(std::string const &msg);
							IrcMessage(IrcMessage const &other);
							~IrcMessage(void);
		IrcMessageError		parse(std::string const &msg, size_t start = 0);
		IrcMessageError		getError(void) const;
		BNFFind	const		&getPrefix(void) const;
		BNFFind const		&getCommand(void) const;
		BNFFind const		&getParams(void) const;
		IrcMessage			&operator=(IrcMessage const &other);
};
