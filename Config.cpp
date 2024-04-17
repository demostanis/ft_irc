/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:06:23 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/14 18:56:13 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Config.hpp"

static BNFVar	_kvParser(void)
{
	BNFChar	eq("eq", '=');
	BNFVar	BLANK("BLANK", BNFChar(' ') | BNFChar('\t'));
	BNFVar  nowheq("nowheq", BNFRange(0x01, 0x07) | BNFRange(0x0E, 0x1F)
			| BNFRange (0x21, 0x3C) | BNFRange(0x3E, 0XFF));
	BNFVar	nowh("nowh", nowheq | eq);
	BNFVar	key("key", nowheq & *(nowheq | (*BLANK & nowheq)));
	BNFVar	value("value", nowh & *(nowh | (*BLANK & nowh)));
	BNFVar	kv("kv", *BLANK & key & *BLANK & eq & *BLANK & value & *BLANK);

	return (kv);
}

char const	*Config::mandatoryKeys[] = {
	"password",
	"source",
	"chanlimit",
	"channellen",
	"source",
	"nicklen",
	NULL
};

BNFVar Config::kvParser(_kvParser());

std::string			Config::parseError(std::string const &filename, size_t lineCount)
{
	return (filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(Config::kvParser.size() + 1));
}

Config::Config(void)
{
}

void				Config::read(std::string const &filename)
{
	std::ifstream	file(filename.c_str());
	size_t			lineCount(1);
	std::string		line;
	BNFFind			key;
	BNFFind			value;
	t_uint			cr;

	if (!file.is_open())
		throw std::invalid_argument(filename + ": " + strerror(errno));
	while (!file.eof())
	{
		getline(file, line);
		if (line.empty())
			break;
		Config::kvParser.parse(line);

		kdo::State	state = Config::kvParser.getState();
		key = Config::kvParser.find("key", 3);
		value = Config::kvParser.find("value", 3);
		if (Config::kvParser.getState().fail())
		{
			if (key.empty())
				throw std::runtime_error(Config::parseError(filename, lineCount) + ": missing key");
			else if (key[0].getState().fail())
				throw std::runtime_error(Config::parseError(filename, lineCount) + ": invalid key");
			else if (Config::kvParser.find("eq", 3).good().empty())
				throw std::runtime_error(Config::parseError(filename, lineCount) + ": missing '='");
			else if (value.empty())
				throw std::runtime_error(Config::parseError(filename, lineCount) + ": missing value");
			else if (value[0].getState().fail())
				throw std::runtime_error(Config::parseError(filename, lineCount) + ": invalid value");
			else
				throw std::runtime_error(Config::parseError(filename, lineCount));
		}
		(*this)[key[0].string()] = value[0].string();
		lineCount++;
	}
	for (cr = 0; Config::mandatoryKeys[cr]; cr++)
	{
		if (!this->contains(Config::mandatoryKeys[cr]))
			throw std::runtime_error(filename + ": missing " + Config::mandatoryKeys[cr]);
	}
}

bool	Config::contains(std::string const &key)
{
	return (this->find(key) != this->end());
}
