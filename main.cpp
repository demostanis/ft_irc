/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:08:09 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/08 18:05:51 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

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

int	main(int argc, char **argv)
{
	Config		config;
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
	std::cout << "  Admin: " << config.admin << std::endl;
}
