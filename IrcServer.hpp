/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/18 01:20:19 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <queue>
#include <iomanip>
#include <sys/epoll.h>
#include "IrcMessage.hpp"
#include "IrcClient.hpp"
#include "kdolib/kdolib.hpp"

#define IRC_SERVER_BACKLOG		128
#define IRC_SERVER_DEFAUT_PORT	"ircd"

class IrcServer: public SocketTcpServer
{
	private:
		std::map<int, std::string>  lineBuf;
		std::queue<IrcMessage>		msgQueue;
		int							epoll;

	public:
				IrcServer(std::string const &port = IRC_SERVER_DEFAUT_PORT);
				~IrcServer(void);
		int     accept(IrcClient *&client);
		int		reveiveMessage(int clientSocket);
		int		getNextMessage(IrcMessage &msg);
		int		connectClient(void);
		int		disconnectClient(int clientSocket);
		int     getClient(IrcClient *&client, int clientSocket);
		bool	isNickInUse(std::string nick);
		int		connect(std::string const &port = IRC_SERVER_DEFAUT_PORT);
		void	disconnect(void);
};
