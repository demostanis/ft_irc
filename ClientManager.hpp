/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:41:28 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 21:28:56 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include "IrcClient.hpp"
#include "IrcMessage.hpp"

class ClientManager
{
private:
	static std::map<int, IrcClient*>	clients;

public:
	static void				registerClient(SocketTcpClient *client);
	static void				unregisterClient(int fd);
	static IrcClient		*getClient(int fd);
	static void				broadcast(std::string msg);
};
