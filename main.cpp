/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:08:09 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 20:43:33 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "IrcServer.hpp"
#include <algorithm>

#include "commands/Nick.hpp"
#include "commands/Pass.hpp"

typedef void	(*command)(IrcMessage&);

static command		commandHandlers[] = {
	&Nick::handle,
	&Pass::handle,
};
static std::string	commandNames[] = {
	"NICK",
	"PASS",
};

Config		config;

// TODO: parse the config with BNF
bool	parse_config(std::string filename, Config &config)
{
	bool	succeeded = false;

	try
	{
		config.read(filename);
		config.parse();
		succeeded = true;
	}
	catch (Config::ParseError &e)
	{
		std::cerr <<
			"error parsing " <<
			filename << ": " <<
			e.what() << std::endl;
	}
	catch (Config::MissingError &e)
	{
		std::cerr <<
			"error checking " <<
			filename << ": " <<
			e.what() << std::endl;
	}
	return (succeeded);
}

std::string	&toUppercase(std::string &str)
{
	std::string::iterator	it;

	for (it = str.begin(); it != str.end(); it++)
		*it = toupper(*it);
	return (str);
}

static void	commandNotFound(std::string command, IrcMessage &msg)
{
	msg.replyError(ERR_UNKNOWNCOMMAND, command + " :Unknown command");
}

static void	handleCommand(IrcMessage &msg)
{
	bool		found;
	std::string	command;
	size_t		i;

	found = false;
	command = msg.getCommand()[0].getValue();
	for (i = 0; i < sizeof(commandNames)/sizeof(commandNames[0]); i++)
	{
		if (commandNames[i] == toUppercase(command))
		{
			commandHandlers[i](msg);
			found = true;
		}
	}
	if (!found)
		commandNotFound(command, msg);
}

static int	listenForConnections(void)
{
	BNFFind::const_iterator	cr;
	IrcMessage				msg;
	IrcServer				server;
	std::string				command;
	
	if (!server.isConnected())
	{
		std::cerr << "failed to start server" << std::endl;
		return (1);
	}
	while (1)
	{
		if (server.getNextMessage(msg))
		{
			std::cout << "failed to read message" << std::endl;
			continue ;
		}
		if (msg.getCommand().size() > 0)
			handleCommand(msg);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	std::string	filename;

	if (argc != 2)
	{
		std::cerr << "too few arguments" << std::endl;
		return (1);
	}
	filename = argv[1];
	if (!parse_config(filename, config))
		return (1);
	std::cout << "Welcome to ircserv!" << std::endl;
	std::cout << "  Prefix: " << config.prefix << std::endl;
	std::cout << "  Admin: " << config.admin << std::endl;
	return (listenForConnections());
}
