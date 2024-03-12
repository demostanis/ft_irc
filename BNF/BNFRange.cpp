/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRange.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 00:06:58 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFRange.hpp"

BNFRange::BNFRange(std::string const &name, char cMin, char cMax):	BNFParser(name),
																	cMin(cMin),
																	cMax(cMax)	
{
}

BNFRange::BNFRange(BNFRange const &other):	BNFParser(other),
											cMin(other.cMin),
											cMax(other.cMax)
{
}

BNFRange::~BNFRange(void)
{
}

void		BNFRange::reset(void)
{
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
	this->value.clear();
}

BNFParser	*BNFRange::clone(void) const
{
	return (new BNFRange(*this));
}

ssize_t		BNFRange::parse(std::string const &str, size_t start)
{
	this->value.clear();
	if (str.length() < start || str[start] < this->cMin || this->cMax < str[start])
	{
		this->errorPos = start;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, 1);
	this->errorPos = BNF_ERROR_POS_NONE;
	return (1);
}

BNFAlts		BNFRange::operator|(BNFParser const &other)
{
        return (BNFAlts(this->name + "|(" + other.getName() + ')', 2, this, &other));
}

BNFCat      BNFRange::operator&(BNFParser const &other)
{
        return (BNFCat(this->name + "&(" + other.getName() + ')', 2, this, &other));
}

BNFRep      BNFRange::operator+(size_t max)
{
        std::string     maxStr;

        kdo::convert(maxStr, max);
        return (BNFRep(this->name + '+' + maxStr, *this, 0, max));
}

BNFRep      BNFRange::operator-(size_t min)
{
        std::string     minStr;

        kdo::convert(minStr, min);
        return (BNFRep(this->name + '-' + minStr, *this, min, BNF_INFINI));
}

BNFFind		*BNFRange::operator[](std::string const &name) const
{
	BNFFind	*res(new BNFFind());

	if (this->name == name)
		res->pushBack(BNFInher(*this));
	return (res);
}

BNFRange	&BNFRange::operator=(BNFRange const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->cMin = other.cMin;
	this->cMax = other.cMax;
	return (*this);
}
