/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:00:46 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/27 10:32:32 by cgodard          ###   ########.fr       */
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

void	motd(IrcClient *client);
void	lusers(IrcServer &server, IrcClient *client);
