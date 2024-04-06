/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:00:46 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/06 02:06:50 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <queue>
#include <algorithm>
#include <sys/epoll.h>
#include "kdolib/kdolib.hpp"
#include "Config.hpp"
#include "IrcChannel.hpp"
#include "IrcServer.hpp"
#include "IrcClient.hpp"
#include "IrcMessage.hpp"

#define IRC_NAME "ircserv"

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

void	motd(IrcClient *client);
void	lusers(IrcServer &server, IrcClient *client);
void	quit(IrcClient *client, std::string reason);
