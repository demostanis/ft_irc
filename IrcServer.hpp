/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 22:03:14 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

#define IRC_SERVER_DEFAULT_BACKLOG	128
#define IRC_SERVER_DEFAULT_PORT		"ircd"

class Config;
class IrcMessage;
class IrcClient;

class IrcServer: public SocketTcpServer
{
	private:
		std::map<int, std::string>  lineBuf;
		std::queue<IrcMessage>		msgQueue;
		Config						config;
		int							epoll;

	public:
						IrcServer(std::string const &filename);
						~IrcServer(void);
		int     		accept(IrcClient *&client);
		int				receiveMessage(int clientSocket);
		int				getNextMessage(IrcMessage &msg);
		int				connectClient(void);
		int				disconnectClient(int clientSocket);
		int     		getClient(IrcClient *&client, int clientSocket);
		bool			isNickInUse(std::string nick);
		int				userCount(void);
		int				connect(std::string const &filename);
		void			disconnect(void);
		Config			&getConfig(void);
};
