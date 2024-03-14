/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:39:56 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFCat.hpp"

BNFCat::BNFCat(std::string const &name, t_uint count, ...): BNFParser(name)
{
	va_list	argList;

	va_start(argList, count);
	while (count--)
		this->rules.push_back(va_arg(argList, BNFParser *)->clone());
	va_end(argList);
}

BNFCat::BNFCat(t_uint count, ...): BNFParser("")
{
	va_list		argList;
	BNFParser	*cr;

	va_start(argList, count);
	while (count--)
	{
		cr = va_arg(argList, BNFParser *)->clone();
		this->rules.push_back(cr);
		this->name += cr->getFormatName();
		if (count)
			this->name += '&';
	}
	va_end(argList);
}

BNFCat::BNFCat(BNFCat const &other):	BNFParser(other)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
}

BNFCat::~BNFCat(void)
{
	std::vector<BNFParser *>::iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
}

std::string BNFCat::getFormatName(void) const
{
    return ('(' + this->name + ')');
}

void		BNFCat::reset(void)
{
	std::vector<BNFParser *>::iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		(*cr)->reset();
	this->value.clear();
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
}

BNFParser	*BNFCat::clone(void) const
{
	return (new BNFCat(*this));
}

ssize_t		BNFCat::parse(std::string const &str, size_t start)
{
	ssize_t								finalLen(0);
	ssize_t								len;
	std::vector<BNFParser *>::iterator	cr;

	this->value.clear();
	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
	{
		len = (*cr)->parse(str, start + finalLen);
		this->value += (*cr)->getValue();
		if (len == BNF_PARSE_ERROR)
			break;
		finalLen += len;	
	}
	if (cr != this->rules.end())
	{
		this->errorPos = (*cr)->getErrorPos();
		while (++cr != this->rules.end())
			(*cr)->reset();
		return (BNF_PARSE_ERROR);
	}
	this->errorPos = BNF_ERROR_POS_NONE;
	return (finalLen);
}

BNFAlts     BNFCat::operator|(BNFParser const &other) const
{
	return (BNFAlts(this->getFormatName() + '|' + other.getFormatName(), 2, this, &other));
}

BNFAlts      BNFCat::operator|(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFAlts      BNFCat::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat      BNFCat::operator&(BNFParser const &other) const
{
	BNFCat	res(*this);

	res.name += '&' + other.getFormatName();
	res.rules.push_back(other.clone());
	return (res);
}

BNFCat      BNFCat::operator&(std::string const &str) const
{
    BNFString	*tmp(new BNFString(str));
	BNFCat		res(*this);

	res.name += '&' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFCat      BNFCat::operator&(char c) const
{
    BNFChar	*tmp(new BNFChar(c));
	BNFCat	res(*this);

	res.name += '&' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFRep      BNFCat::operator+(size_t max) const
{
	return (BNFRep(this->getFormatName() + '+' + kdo::itoa(max), *this, 0, max));
}

BNFRep		BNFCat::operator-(size_t min) const
{
	return (BNFRep(this->getFormatName() + '-' + kdo::itoa(min), *this, min, BNF_INFINI));
}

BNFFind		BNFCat::operator[](std::string const &name) const
{
	BNFFind										res;
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		res.merge((**cr)[name]);
	res.pushParent(*this);
	if (this->name == name)
		res.push_back(BNFInher(*this));
	return (res);
}

BNFCat		&BNFCat::operator=(BNFCat const &other)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
	return (*this);
}
