/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/18 13:59:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include <arpa/inet.h>

#define IRC_SERVER_DEFAULT_BACKLOG	128
#define IRC_SERVER_DEFAULT_PORT		"ircd"

class Config;
class IrcMessage;
class IrcClient;
class IrcChannel;

class IrcServer: public TcpServer
{
	private:
		std::map<int, std::string>  		lineBuf;
		std::map<std::string, IrcChannel>	channels;
		std::queue<IrcMessage *>			msgQueue;
		Config								config;
		int									epoll;

		static std::string	findIp(struct sockaddr_storage *addr);

	public:
						IrcServer(std::string const &filename);
						~IrcServer(void);
		int     		accept(IrcClient *&client);
		int				receiveMessage(int clientSocket);
		int				getNextMessage(IrcMessage *&msg);
		int				connectClient(void);
		int				disconnectClient(int clientSocket);
		int     		getClient(IrcClient *&client, int clientSocket);
		bool			isNickInUse(std::string const &nick);
		IrcClient		*getClientByNick(std::string const &nick);
		int				userCount(void);
		bool			channelExists(std::string const &name);
		IrcChannel		*getChannel(std::string const &name);
		IrcChannel		*createChannelIfNeeded(std::string const &name);
		int				connect(std::string const &filename);
		void			disconnect(void);
		Config			&getConfig(void);

};
