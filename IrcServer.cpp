/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/16 20:44:50 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"
#include "ClientManager.hpp"

IrcServer::IrcServer(std::string const &port):	epoll(INVALID_FD)
{
	this->connect(port);
}

IrcServer::~IrcServer(void)
{
	this->disconnect();
}

int	IrcServer::reveiveMessage(int clientSocket)
{
	SocketTcpClient	*client;
	std::string		str;
	std::string		line;
	size_t			lineStart;
	size_t			lineEnd;
	IrcMessage		msg(clientSocket);

	if (this->getClient(client, clientSocket))
		return (EXIT_FAILURE);
	if (client->recv(str, MSG_DONTWAIT) < 0)
		return (EXIT_FAILURE);
	line = this->lineBuf[clientSocket] + str;
	lineStart = 0;
	lineEnd = line.find('\n');
	while (lineEnd != std::string::npos)
	{
		msg.parse(line, lineStart);
		this->msgQueue.push(msg);
		lineStart = lineEnd + 1;
		lineEnd = line.find('\n', lineStart);
	}
	this->lineBuf[clientSocket] = line.substr(lineStart);
	return (EXIT_SUCCESS);
}

int		IrcServer::getNextMessage(IrcMessage &msg)
{
	struct epoll_event	events[IRC_SERVER_BACKLOG];
	int					readyFd;

	while (this->msgQueue.empty())
	{
		readyFd = epoll_wait(this->epoll, events, IRC_SERVER_BACKLOG, -1);
		for (int i(0); i < readyFd; i++)
		{
			if (events[i].events & (EPOLLRDHUP | EPOLLHUP))
			{
				if (events[i].data.fd == this->getFd())
				{
					std::cerr << "connection closed" << std::endl;
					return (EXIT_FAILURE);
				}
				else
					this->disconnectClient(events[i].data.fd);
			}
			else
			{
				if (events[i].data.fd == this->getFd())
					this->connectClient();
				else
					this->reveiveMessage(events[i].data.fd);
			}
		}
	}
	msg = this->msgQueue.front();
	this->msgQueue.pop();
	return (EXIT_SUCCESS);
}

int		IrcServer::connectClient(void)
{
	SocketTcpClient		*newClient;
	struct epoll_event	event = {};

	if (this->SocketTcpServer::accept(newClient))
		return (perror("accept"), EXIT_ERRNO);
	ClientManager::registerClient(newClient);
	event.events = EPOLLIN | EPOLLRDHUP;
	event.data.fd = newClient->getFd();
	if (epoll_ctl(this->epoll, EPOLL_CTL_ADD, newClient->getFd(), &event))
	{
		perror("epoll_ctl");
		this->SocketTcpServer::disconnectClient(newClient->getFd());
		return (EXIT_ERRNO);
	}
	std::cout << "[" << newClient->getFd() << "]: connect" << std::endl;
	return (EXIT_SUCCESS);
}

int		IrcServer::disconnectClient(int clientSocket)
{
	ClientManager::unregisterClient(clientSocket);
	this->SocketTcpServer::disconnectClient(clientSocket);
	this->lineBuf[clientSocket].clear();
	std::cout << "[" << clientSocket << "]: disconnect" << std::endl;
	return (epoll_ctl(this->epoll, EPOLL_CTL_DEL, clientSocket, NULL));
}

int		IrcServer::connect(std::string const &port)
{
	struct epoll_event  event = {};
	int					error;

	error = this->SocketTcpServer::connect(port, IRC_SERVER_BACKLOG);
	if (error)
	{
		if (error != EXIT_ERRNO)
			std::cout << "ip error: " << gai_strerror(error) << std::endl;
		else
			perror("connection failed");
		return (error);
	}
	this->epoll = epoll_create(this->getBacklog());
	if (this->epoll == INVALID_FD)
	{
		perror("epoll_create");
		this->disconnect();
		return (EXIT_ERRNO);
	}
	event.events = EPOLLIN | EPOLLRDHUP;
	event.data.fd = this->getFd();
	if (epoll_ctl(this->epoll, EPOLL_CTL_ADD, this->getFd(), &event))
	{
		perror("epoll_ctl");
		this->disconnect();
		return (EXIT_ERRNO);
	}
	return (EXIT_SUCCESS);
}

void	IrcServer::disconnect(void)
{
	this->SocketTcpServer::disconnect();
	if (this->epoll != INVALID_FD)
		::close(this->epoll);
}
