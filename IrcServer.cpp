/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/14 19:33:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "IrcServer.hpp"

IrcServer::IrcServer(std::string const &filename):	epoll(INVALID_FD)
{
	this->connect(filename);
}

IrcServer::~IrcServer(void)
{
	this->disconnect();
}

int				IrcServer::accept(IrcClient *&client)
{
	struct sockaddr_storage clientAddr;
    socklen_t               addrSize;
    int                     clientSocket;

    addrSize = sizeof(clientAddr);
    clientSocket = ::accept(this->fd, (struct sockaddr *)&clientAddr, &addrSize);
    if (clientSocket == INVALID_FD)
        return (EXIT_ERRNO);
    this->clients[clientSocket] = new IrcClient(this->config, clientSocket);
    client = static_cast<IrcClient *>(this->clients[clientSocket]);
    return (EXIT_SUCCESS);
}

int				IrcServer::receiveMessage(int clientSocket)
{
	IrcClient		*client;
	std::string		str;
	std::string		line;
	size_t			lineStart;
	size_t			lineEnd;
	IrcMessage		*msg;

	if (this->getClient(client, clientSocket))
		return (EXIT_FAILURE);
	if (client->recv(str, MSG_DONTWAIT) < 0)
		return (EXIT_FAILURE);
	line = this->lineBuf[clientSocket] + str;
	lineStart = 0;
	lineEnd = line.find('\n');
	while (lineEnd != std::string::npos)
	{
		msg = new IrcMessage(client, line, lineStart);
		this->msgQueue.push(msg);
		lineStart = lineEnd + 1;
		lineEnd = line.find('\n', lineStart);
	}
	this->lineBuf[clientSocket] = line.substr(lineStart);
	return (EXIT_SUCCESS);
}

int				IrcServer::getNextMessage(IrcMessage *&msg)
{
	struct epoll_event	events[this->backlog];
	int					readyFd;

	while (this->msgQueue.empty())
	{
		readyFd = epoll_wait(this->epoll, events, this->backlog, -1);
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
					this->receiveMessage(events[i].data.fd);
			}
		}
	}
	msg = this->msgQueue.front();
	this->msgQueue.pop();
	return (EXIT_SUCCESS);
}

int				IrcServer::connectClient(void)
{
	IrcClient		 	*newClient;
	struct epoll_event	event = {};

	if (this->accept(newClient))
		return (perror("accept"), EXIT_ERRNO);
	event.events = EPOLLIN | EPOLLRDHUP;
	event.data.fd = newClient->getFd();
	if (epoll_ctl(this->epoll, EPOLL_CTL_ADD, newClient->getFd(), &event))
	{
		perror("epoll_ctl");
		this->TcpServer::disconnectClient(newClient->getFd());
		return (EXIT_ERRNO);
	}
	std::cout << "[" << newClient->getFd() << "]: connect" << std::endl;
	return (EXIT_SUCCESS);
}

int		IrcServer::disconnectClient(int clientSocket)
{
	IrcClient	*client;

	if (this->getClient(client, clientSocket))
	{
		if (!client->isConnected())
			return (EXIT_SUCCESS);
		quit(client, "disconnect");
	}
	this->TcpServer::disconnectClient(clientSocket);
	this->lineBuf[clientSocket].clear();
	std::cout << "[" << clientSocket << "]: disconnect" << std::endl;
	return (epoll_ctl(this->epoll, EPOLL_CTL_DEL, clientSocket, NULL));
}

int				IrcServer::getClient(IrcClient *&client, int clientSocket)
{
	std::map<int, TcpClient *>::iterator  cr;

    cr = this->clients.find(clientSocket);
    if (cr == this->clients.end())
        return (EXIT_FAILURE);
    client = static_cast<IrcClient *>(cr->second);
    return (EXIT_SUCCESS);
}

bool			IrcServer::isNickInUse(std::string const &nick)
{
	std::map<int, TcpClient *>::iterator	cr;

	for (cr = this->clients.begin(); cr != clients.end(); cr++)
	{
		if (!kdo::stricmp(static_cast<IrcClient *>(cr->second)->getNick(), nick))
			return (true);
	}
	return (false);
}

IrcClient		*IrcServer::getClientByNick(std::string const &nick)
{
	std::map<int, TcpClient *>::iterator	cr;

	for (cr = this->clients.begin(); cr != clients.end(); cr++)
	{
		if (!kdo::stricmp(static_cast<IrcClient *>(cr->second)->getNick(), nick))
			return (static_cast<IrcClient *>(cr->second));
	}
	return (NULL);
}

int				IrcServer::userCount(void)
{
	return (std::distance(this->clients.begin(), this->clients.end()));
}

int				IrcServer::connect(std::string const &filename)
{
	std::string			port = IRC_SERVER_DEFAULT_PORT;
	struct epoll_event  event = {};
	int					error;

	try
	{
		this->config.read(filename);
	}
	catch (std::invalid_argument const &e)
	{
		std::cerr << IRC_NAME << ": " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	catch (std::runtime_error const &e)
	{
		std::cerr << IRC_NAME << ": parse error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	if (this->config.contains("port"))
		port = this->config["port"];

	// I know you hate macros but it's so much shorter
#define CHECK_INT(name, defaultValue) \
	int name = defaultValue; \
	if (this->config.contains(#name)) \
	{ \
		if (!kdo::allConverted(kdo::convert(name, this->config[#name]))) \
		{ \
			std::cerr << IRC_NAME << ": " << this->config[#name] << ": invalid "#name << std::endl; \
			return (EXIT_FAILURE); \
		} \
	}
	CHECK_INT(backlog, IRC_SERVER_DEFAULT_BACKLOG);
	CHECK_INT(chanlimit, 0);
	CHECK_INT(channellen, 0);
	CHECK_INT(nicklen, 0);

	error = this->TcpServer::connect(port, backlog);
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

void			IrcServer::disconnect(void)
{
	this->TcpServer::disconnect();
	if (this->epoll != INVALID_FD)
		::close(this->epoll);
}

bool	IrcServer::channelExists(std::string const &name)
{
	return (channels.find(name) != channels.end());
}

IrcChannel		*IrcServer::getChannel(std::string const &name)
{
	return (&channels[name]);
}

IrcChannel		*IrcServer::createChannelIfNeeded(std::string const &name)
{
	if (channels.find(name) == channels.end())
		channels[name].setName(name);
	return (&channels[name]);
}

Config			&IrcServer::getConfig(void)
{
	return (this->config);
}
