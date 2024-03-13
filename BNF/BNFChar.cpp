/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 03:05:06 by nlaerema         ###   ########.fr       */
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

BNFAlts		BNFChar::operator|(BNFParser const &other) const
{
	return (BNFAlts(this->name + "|(" + other.getName() + ')', 2, this, &other));
}

BNFAlts      BNFChar::operator|(std::string const &str) const
{
    BNFString   tmp(str, str);

    return (BNFAlts(this->name + '|' + str, 2, this, &tmp));
}

BNFAlts      BNFChar::operator|(char c) const
{
    BNFChar   tmp((char[2]){c, '\0'}, c);

    return (BNFAlts(this->name + '|' + c, 2, this, &tmp));
}

BNFCat		BNFChar::operator&(BNFParser const &other) const
{
	return (BNFCat(this->name + "&(" + other.getName() + ')', 2, this, &other));
}

BNFCat		BNFChar::operator&(std::string const &str) const
{
	BNFString	tmp(str, str);

	return (BNFCat(this->name + '&' + str, 2, this, &tmp));
}

BNFCat      BNFChar::operator&(char c) const
{
    BNFChar   tmp((char[2]){c, '\0'}, c);

    return (BNFCat(this->name + '&' + c, 2, this, &tmp));
}

BNFRep		BNFChar::operator+(size_t max) const
{
	std::string	maxStr;

	kdo::convert(maxStr, max);
	return (BNFRep(this->name + '+' + maxStr, *this, 0, max));
}

BNFRep		BNFChar::operator-(size_t min) const
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
