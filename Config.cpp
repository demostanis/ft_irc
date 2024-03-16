/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:06:23 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 20:54:50 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config()
{
}

Config::~Config()
{
}

static bool	allowedKey(std::string &key)
{
	bool	found;

	found = false;
	for (size_t	i = 0; i < sizeof(allowedKeys)/sizeof(*allowedKeys); ++i)
	{
		if (allowedKeys[i] == key)
			found = true;
	}
	return (found);
}

void	Config::read(std::string filename) throw(ParseError)
{
	std::ifstream	file(filename.c_str());
	std::string		key;
	std::string		value;
	char			equal;

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> key;
			file >> equal;
			if (key.empty())
				continue ;
			if (equal != '=')
				throw ParseError("missing '='");
			file >> value;
			if (value.empty())
				throw ParseError("missing value");
			if (file.bad())
				throw ParseError("invalid token");
			if (!allowedKey(key))
				throw ParseError("invalid key");
			kv[key] = value;
		}
	}
	else
		throw ParseError("failed to open file");
}

#define GET_ONE(key, T, default)                      \
{                                                     \
	std::pair<bool, T>	elem;                         \
	if ((elem = get<T>(#key)).first)                  \
		key = elem.second;                            \
	else                                              \
		key = default;                                \
}

#define REQUIRE_ONE(key, T)                           \
{                                                     \
	std::pair<bool, T>	elem;                         \
	if ((elem = get<T>(#key)).first)                  \
		key = elem.second;                            \
	else                                              \
		throw MissingError("missing field " # key);   \
}

void	Config::parse(void) throw(MissingError)
{
	REQUIRE_ONE(admin, std::string);
	REQUIRE_ONE(prefix, std::string);
	REQUIRE_ONE(password, std::string);
}
