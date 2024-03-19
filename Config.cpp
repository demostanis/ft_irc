/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:06:23 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 21:42:07 by cgodard          ###   ########.fr       */
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
	BNFVar	key("key", nowheq & (nowheq | (BLANK - 0 & nowheq)) - 0);
	BNFVar	value("value", nowh & (nowh | (BLANK - 0 & nowh)) - 0);
	BNFVar	kv("kv", BLANK - 0 & key & BLANK - 0 & eq & BLANK - 0 & value & BLANK - 0 & '\0');

	return (kv);
}

char const	*Config::mandatoryKeys[] = {
	"admin",
	"password",
	"source",
	"chanlimit",
	"channellen",
	"source",
	"nicklen",
	NULL
};

BNFVar Config::kvParser(_kvParser());


Config::Config(void)
{
}

void				Config::read(std::string const &filename)
{
	std::ifstream	file(filename.c_str());
	t_uint			lineCount(1);
	ssize_t			errorPos;
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
		key = Config::kvParser.find("key", 3);
		value = Config::kvParser.find("value", 3);
		errorPos = Config::kvParser.getErrorLen();
		if (errorPos != BNF_ERROR_LEN_NONE)
		{
			errorPos++;
			if (key.empty())
				throw std::runtime_error(filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(errorPos) + ": missing key");
			else if (key[0].getErrorLen() != BNF_ERROR_LEN_NONE)
				throw std::runtime_error(filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(errorPos) + ": invalid key");
			else if (Config::kvParser.find("eq", 3).isSuccess().empty())
				throw std::runtime_error(filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(errorPos) + ": missing '='");
			else if (value.empty())
				throw std::runtime_error(filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(errorPos) + ": missing value");
			else if (value[0].getErrorLen() != BNF_ERROR_LEN_NONE)
				throw std::runtime_error(filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(errorPos) + ": invalid value");
			else
				throw std::runtime_error(filename + ':' + kdo::itoa(lineCount) + ':' + kdo::itoa(errorPos));
		}
		(*this)[key[0].getValue()] = value[0].getValue();
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
