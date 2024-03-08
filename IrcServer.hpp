/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/08 12:37:58 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <queue>
#include <csignal>
#include <iomanip>
#include <sys/epoll.h>
#include "SocketTcpClient.hpp"
#include "SocketTcpServer.hpp"

#define IRC_SERVER_DEFAUT_PORT "ircd"

class IrcServer: public SocketTcpServer
{
	private:
		std::queue<std::string>	commandQueue;
		int						epoll;

	public:
				IrcServer(void);
				IrcServer(std::string const &addr, std::string const &port = IRC_SERVER_DEFAUT_PORT);
				~IrcServer(void);
		int		getNextCommand(std::string &command);
		int		connectClient(void);
		int		disconnectClient(int clientSocket);
		int		connect(std::string const &addr, std::string const &port = IRC_SERVER_DEFAUT_PORT);
		bool	isConnected(void);
};
