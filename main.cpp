/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:08:09 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/20 03:41:13 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

typedef void	(*command)(IrcServer &, IrcMessage &);

static command		commandHandlers[] = {
	&Nick::handle,
	&Pass::handle,
	&User::handle,
	&Cap::handle,
	&Ping::handle,
	&Lusers::handle,
	&Motd::handle,
	&Join::handle,
};
static std::string	commandNames[] = {
	"NICK",
	"PASS",
	"USER",
	"CAP",
	"PING",
	"LUSERS",
	"MOTD",
	"JOIN",
};

static void	commandNotFound(std::string command, IrcMessage &msg)
{
	msg.replyError(ERR_UNKNOWNCOMMAND, command + " :Unknown command");
}

static void	handleCommand(IrcServer &server, IrcMessage &msg)
{
	bool		found;
	std::string	command;
	size_t		i;

	found = false;
	command = msg.getCommand()[0].getValue();
	for (i = 0; i < sizeof(commandNames)/sizeof(commandNames[0]); i++)
	{
		if (commandNames[i] == kdo::toUppercase(command))
		{
			commandHandlers[i](server, msg);
			found = true;
		}
	}
	if (!found)
		commandNotFound(command, msg);
}

static int	listenForConnections(std::string const &filename)
{
	IrcServer	server(filename);
	IrcMessage	msg;
	
	if (!server.isConnected())
	{
		std::cerr << IRC_NAME << ": connection failed" << std::endl;
		return (EXIT_FAILURE);
	}
	std::cout << "Welcome to ircserv!" << std::endl;
	std::cout << "  Source: " << server.getConfig()["source"] << std::endl;
	std::cout << "  Admin: " << server.getConfig()["admin"] << std::endl;
	while (1)
	{
		if (server.getNextMessage(msg))
			break;
		if (msg.getCommand().size() > 0)
			handleCommand(server, msg);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << IRC_NAME << ": too few arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	return (listenForConnections(argv[1]));
}
