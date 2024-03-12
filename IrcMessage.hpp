/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 18:27:21 by nlaerema         ###   ########.fr       */
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
