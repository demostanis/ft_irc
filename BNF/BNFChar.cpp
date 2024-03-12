/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 00:04:10 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFChar.hpp"

BNFChar::BNFChar(std::string const &name, char c):	BNFParser(name),
													c(c)
{
}

BNFChar::BNFChar(BNFChar const &other): BNFParser(other),
										c(other.c)
{
}

BNFChar::~BNFChar(void)
{
}

void		BNFChar::reset(void)
{
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
	this->value.clear();
}

BNFParser	*BNFChar::clone(void) const
{
	return (new BNFChar(*this));
}

ssize_t		BNFChar::parse(std::string const &str, size_t start)
{
	this->value.clear();
	if (str.length() < start || str[start] != this->c)
	{
		this->errorPos = start;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, 1);
	this->errorPos = BNF_ERROR_POS_NONE;
	return (1);
}

BNFAlts		BNFChar::operator|(BNFParser const &other)
{
	return (BNFAlts(this->name + "|(" + other.getName() + ')', 2, this, &other));
}

BNFCat		BNFChar::operator&(BNFParser const &other)
{
	return (BNFCat(this->name + "&(" + other.getName() + ')', 2, this, &other));
}

BNFRep		BNFChar::operator+(size_t max)
{
	std::string	maxStr;

	kdo::convert(maxStr, max);
	return (BNFRep(this->name + '+' + maxStr, *this, 0, max));
}

BNFRep		BNFChar::operator-(size_t min)
{
	std::string	minStr;

	kdo::convert(minStr, min);
	return (BNFRep(this->name + '-' + minStr, *this, min, BNF_INFINI));
}

BNFFind		*BNFChar::operator[](std::string const &name) const
{
	BNFFind	*res(new BNFFind());

	if (this->name == name)
		res->pushBack(BNFInher(*this));
	return (res);
}

BNFChar		&BNFChar::operator=(BNFChar const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->c = other.c;
	return (*this);
}
