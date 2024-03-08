/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/08 12:56:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

static int	g_sigint(0);

void	sigintHandler(int sig)
{
	if (sig == SIGINT)
	{
		std::cout << std::endl;
		g_sigint = 1;
	}
}

IrcServer::IrcServer(void): epoll(INVALID_FD)
{
}

IrcServer::IrcServer(std::string const &addr, std::string const &port):	epoll(INVALID_FD)
{
	this->connect(addr, port);
}

IrcServer::~IrcServer(void)
{
	if (this->epoll != INVALID_FD)
		::close(epoll);
}

int		IrcServer::getNextCommand(std::string &command)
{
	struct epoll_event	events[this->SocketTcpServer::getBacklog()];
	int					readyFd;

	std::signal(SIGINT, sigintHandler);
	while (!g_sigint)
	{
		readyFd = epoll_wait(this->epoll, events, this->SocketTcpServer::getBacklog(), -1);
		for (int i(0); i < readyFd; i++)
		{
			if (events[i].events & (EPOLLRDHUP | EPOLLHUP))
			{
				if (events[i].data.fd == this->SocketTcpServer::getFd()
					|| events[i].data.fd == this->SocketTcpClient::getFd())
				{
					std::signal(SIGINT, SIG_DFL);
					std::cerr << "connection closed" << std::endl;
					return (EXIT_FAILURE);
				}
				else
					this->disconnectClient(events[i].data.fd);
			}
			else
			{
				if (events[i].data.fd == this->SocketTcpServer::getFd())
					this->connectClient();
				else if (events[i].data.fd == this->SocketTcpClient::getFd())
					this->receive_out(this->SocketTcpClient::getFd());
				else
					this->receive_in(events[i].data.fd);
			}
		}
	}
	std::signal(SIGINT, SIG_DFL);
	return (EXIT_SUCCESS);
}

int		IrcServer::connectClient(void)
{
	SocketTcpClient		*newClient;
	struct epoll_event	event = {};

	if (this->SocketTcpServer::accept(newClient))
		return (perror("accept"), EXIT_ERRNO);
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
	this->SocketTcpServer::disconnectClient(clientSocket);
	std::cout << "[" << clientSocket << "]: disconnect" << std::endl;
	return (epoll_ctl(this->epoll, EPOLL_CTL_DEL, clientSocket, NULL));
}

int		IrcServer::connect(std::string const &addr, std::string const &port)
{
	struct epoll_event  event = {};
	int					error;

	error = this->SocketTcpServer::connect(port);
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
	event.data.fd = this->SocketTcpClient::getFd();
	if (epoll_ctl(this->epoll, EPOLL_CTL_ADD, this->SocketTcpClient::getFd(), &event))
	{
		perror("epoll_ctl");
		this->SocketTcpServer::disconnect();
		this->SocketTcpClient::disconnect();
		::close(this->epoll);
		return (EXIT_ERRNO);
	}
	event.events = EPOLLIN | EPOLLRDHUP;
	event.data.fd = this->SocketTcpServer::getFd();
	if (epoll_ctl(this->epoll, EPOLL_CTL_ADD, this->SocketTcpServer::getFd(), &event))
	{
		perror("epoll_ctl");
		this->SocketTcpServer::disconnect();
		this->SocketTcpClient::disconnect();
		::close(this->epoll);
		return (EXIT_ERRNO);
	}
	return (EXIT_SUCCESS);
}

bool	IrcServer::isConnected(void)
{
	return (this->SocketTcpClient::isConnected() && this->SocketTcpServer::isConnected());
}

void	IrcServer::disconnect(void)
{
	this->SocketTcpClient::disconnect();
	this->SocketTcpServer::disconnect();
	if (this->epoll != INVALID_FD)
		::close(epoll);
}

int		IrcServer::getAddrError(void)
{
	if (this->SocketTcpClient::getAddrError())
		return (this->SocketTcpClient::getAddrError());
	return (this->SocketTcpServer::getAddrError());
}
