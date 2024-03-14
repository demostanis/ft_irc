/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFString.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:37:46 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFString.hpp"

BNFString::BNFString(std::string const &name, std::string const &str):	BNFParser(name),
																		str(str)
{
}

BNFString::BNFString(std::string const &str):	BNFParser('<' + str + '>'),
												str(str)
{
}

BNFString::BNFString(BNFString const &other):	BNFParser(other),
												str(other.str)
{
}

BNFString::~BNFString(void)
{
}

std::string BNFString::getFormatName(void) const
{
	return (this->name);
}

void		BNFString::reset(void)
{
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
	this->value.clear();
}

BNFParser	*BNFString::clone(void) const
{
	return (new BNFString(*this));
}

ssize_t		BNFString::parse(std::string const &str, size_t start)
{
	this->value.clear();
	if (str.length() < start + this->str.length()
		|| str.compare(start, this->str.length(), this->str))
	{
		this->errorPos = start;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, this->str.length());
	this->errorPos = BNF_ERROR_POS_NONE;
	return (this->str.length());
}

BNFAlts		BNFString::operator|(BNFParser const &other) const
{
	return (BNFAlts(this->getFormatName() + '|' + other.getFormatName(), 2, this, &other));
}

BNFAlts      BNFString::operator|(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFAlts      BNFString::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat		BNFString::operator&(BNFParser const &other) const
{
	return (BNFCat(this->getFormatName() + '&' + other.getFormatName(), 2, this, &other));
}

BNFCat      BNFString::operator&(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat      BNFString::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFRep		BNFString::operator+(size_t max) const
{
	return (BNFRep(this->getFormatName() + '+' + kdo::itoa(max), *this, 0, max));
}

BNFRep		BNFString::operator-(size_t min) const
{
	return (BNFRep(this->getFormatName() + '-' + kdo::itoa(min), *this, min, BNF_INFINI));
}

BNFFind		BNFString::operator[](std::string const &name) const
{
	BNFFind	res;

	if (this->name == name)
		res.push_back(BNFInher(*this));
	return (res);
}

BNFString	&BNFString::operator=(BNFString const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->str = other.str;
	return (*this);
}
