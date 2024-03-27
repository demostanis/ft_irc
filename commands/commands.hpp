/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:46:25 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:53:24 by cgodard          ###   ########.fr       */
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

#define ITER_CHANNEL_CLIENTS(channel)                        \
	std::vector<IrcClient *>::const_iterator        clients; \
	clients = (channel).getClients().begin();                \
	for (; clients != (channel).getClients().end(); ++clients)

#define CLIENT() \
	(*clients)

#define ITER_CLIENT_CHANNELS(client)                              \
	std::map<std::string, IrcChannel*>::const_iterator	channels; \
	channels = (client)->getChannels().begin();                   \
	for (; channels != (client)->getChannels().end(); ++channels)

#define CHANNEL() \
	(channels->second)

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
		return ;                                                           \
	}                                                                      \
	if (!__client || !__client->isRegistered())                            \
	{                                                                      \
		msg.replyError(ERR_NOTREGISTERED, ":You have not registered");     \
		return ;                                                           \
	}

enum
{
	RPL_TOPIC = 332,
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
	RPL_LUSERCLIENT = 251,
	RPL_LUSERME = 255,
	RPL_UMODEIS = 221,
	RPL_MOTD = 372
};

#include "Cap.hpp"
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
