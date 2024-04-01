/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:46:25 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/01 02:43:45 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../irc.hpp"

#define DEFINE_CMD(name, code)                                   \
	namespace name {                                             \
		void	handle(IrcServer &server, IrcMessage &msg) {     \
			IrcClient	*client = msg.getClient();               \
			(void)server; (void)msg; (void)client;               \
			code;                                                \
		}                                                        \
	}

#define N_PARAMS() \
	(msg.getParams().size())

#define PARAM(nth) \
	(msg.getParams()[nth].getValue())

#define ENSURE_AUTH()                                                      \
	IrcClient       *__client = msg.getClient();                           \
	if (!__client || !__client->getHasGivenPassword())                     \
	{                                                                      \
		msg.replyError(ERR_PASSWDMISMATCH,                                 \
			":You haven't provided a password with PASS");                 \
		server.disconnectClient(client->getFd());                          \
		return ;                                                           \
	}                                                                      \
	if (!__client || !__client->isRegistered())                            \
	{                                                                      \
		msg.replyError(ERR_NOTREGISTERED, ":You have not registered");     \
		server.disconnectClient(client->getFd());                          \
		return ;                                                           \
	}

#define ENSURE_OP() \
	IrcClient       *___client = msg.getClient();                                   \
	if (!___client || ___client->getModes().find('o') == std::string::npos)          \
	{                                                                              \
		msg.replyError(ERR_CHANOPRIVSNEEDED,                                       \
			":You're not a channel operator");                                     \
		return ;                                                                   \
	}                                                                              \

enum
{
	RPL_TOPIC = 332,
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
	RPL_LUSERCLIENT = 251,
	RPL_LUSERME = 255,
	RPL_UMODEIS = 221,
	RPL_MOTD = 372,
	RPL_INVITING = 341,
	RPL_CHANNELMODEIS = 324,
};

#include "Noop.hpp"
#include "Join.hpp"
#include "Lusers.hpp"
#include "Mode.hpp"
#include "Motd.hpp"
#include "Nick.hpp"
#include "Pass.hpp"
#include "Ping.hpp"
#include "Privmsg.hpp"
#include "Quit.hpp"
#include "User.hpp"
#include "Part.hpp"
#include "Invite.hpp"
#include "Topic.hpp"
#include "Kick.hpp"
