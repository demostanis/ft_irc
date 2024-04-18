/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:10:35 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/17 19:58:22 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	readConfig(Config &config, const std::string &filename)
{
	try
	{
		config.read(filename);
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
	return (EXIT_SUCCESS);
}

class Bot : public TcpClient
{
	private:
		void				sendCommand(std::string name, std::string content);
		void				respond(const std::string &message);
		void				unknownCommand(const std::string &user);
		void				registerr();
		std::string			name;
		std::string			serverPassword;

	public:
							Bot(Config &config);
							~Bot();
		int					run();
};

Bot::Bot(Config &config) : TcpClient(config["host"], config["port"])
{
	name = config["bot_name"];
	if (name.empty())
		name = "unnamed bot";
	serverPassword = config["password"];
}

Bot::~Bot()
{
	disconnect();
}

void	Bot::sendCommand(std::string commandName, std::string content)
{
	send(commandName + " " + content + CRLF);
}

void	Bot::registerr()
{
	sendCommand("PASS", serverPassword);
	sendCommand("NICK", name);
	sendCommand("USER", name + " " + name + " " + name + " " + name);
}

void	Bot::unknownCommand(const std::string &user)
{
	sendCommand("PRIVMSG", user + " :Unknown command");
}

void	Bot::respond(const std::string &message)
{
	std::string	author;
	std::string	content;
	std::string command;
	std::string args;
	size_t	delim;
	
	delim = message.find("!");
	if (delim == std::string::npos)
		return ;
	author = message.substr(1, delim-1);
	std::cout << "received a message from " << author << std::endl;
	content = message.substr(message.substr(1).find(":")+2);
	content = content.substr(0, content.length()-1); // remove crlf

	if (content.find(' ') == std::string::npos)
	{
		unknownCommand(author);
		return ;
	}
	command = content.substr(0, content.find(' '));
	args = content.substr(content.find(' ')+1);
	if (command == "SAY")
		sendCommand("PRIVMSG", author + " :" + args);
	else
		unknownCommand(author);
}

int	Bot::run()
{
	if (!isConnected())
	{
		std::cerr << IRC_NAME << ": failed to connect" << std::endl;
		std::cerr << IRC_NAME << ": is the server running?" << std::endl;
		return (EXIT_FAILURE);
	}

	registerr();

	std::string	message;
	while (recv(message))
	{
		if (message.find("PRIVMSG") != std::string::npos)
			respond(message);
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

	std::string	filename = argv[1];
	Config	config;

	if (readConfig(config, filename))
		return (EXIT_FAILURE);

	Bot	bot(config);
	if (bot.run())
		return (EXIT_FAILURE);
}
