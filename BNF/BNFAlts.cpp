/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:40:50 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFAlts.hpp"

BNFAlts::BNFAlts(std::string const &name, t_uint count, ...): BNFParser(name)
{
	va_list	argList;

	va_start(argList, count);
	while (count--)
		this->rules.push_back(va_arg(argList, BNFParser *)->clone());
	va_end(argList);
}

BNFAlts::BNFAlts(t_uint count, ...): BNFParser("")
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
			this->name += '|';
	}
	va_end(argList);
}

BNFAlts::BNFAlts(BNFAlts const &other):	BNFParser(other)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
}

BNFAlts::~BNFAlts(void)
{
	std::vector<BNFParser *>::iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
}

std::string BNFAlts::getFormatName(void) const
{
    return ('(' + this->name + ')');
}

void		BNFAlts::reset(void)
{
	std::vector<BNFParser *>::iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		(*cr)->reset();
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
	this->value.clear();
}

BNFParser	*BNFAlts::clone(void) const
{
	return (new BNFAlts(*this));
}

ssize_t		BNFAlts::parse(std::string const &str, size_t start)
{
	ssize_t								finalLen(BNF_PARSE_ERROR);
	ssize_t								finalErrorPos(BNF_ERROR_POS_NONE);
	ssize_t								len;
	std::vector<BNFParser *>::iterator	cr;

	this->value.clear();
	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
	{
		len = (*cr)->parse(str, start);
		finalLen = std::max(finalLen, len);
		finalErrorPos = std::max(finalErrorPos, (*cr)->getErrorPos());
	}
	if (finalLen == BNF_PARSE_ERROR)
	{
		this->value = str.substr(start, finalErrorPos - start);
		this->errorPos = finalErrorPos;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, finalLen);
	this->errorPos = BNF_ERROR_POS_NONE;
	return (finalLen);
}

BNFAlts     BNFAlts::operator|(BNFParser const &other) const
{
	BNFAlts	res(*this);

	res.name += '|' + other.getFormatName();
	res.rules.push_back(other.clone());
	return (res);
}

BNFAlts      BNFAlts::operator|(std::string const &str) const
{
    BNFString   *tmp(new BNFString(str));
	BNFAlts		res(*this);

	res.name += '|' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFAlts      BNFAlts::operator|(char c) const
{
    BNFChar	*tmp(new BNFChar(c));
	BNFAlts	res(*this);

	res.name += '|' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFCat		BNFAlts::operator&(BNFParser const &other) const
{
	return (BNFCat(this->getFormatName() + '&' + other.getFormatName(), 2, this, &other));
}

BNFCat      BNFAlts::operator&(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat      BNFAlts::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFRep      BNFAlts::operator+(size_t max) const
{
	return (BNFRep(this->getFormatName() + '+' + kdo::itoa(max), *this, 0, max));
}

BNFRep      BNFAlts::operator-(size_t min) const
{
	return (BNFRep(this->getFormatName() + '-' + kdo::itoa(min), *this, min, BNF_INFINI));
}

BNFFind		BNFAlts::operator[](std::string const &name) const
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

BNFAlts	&BNFAlts::operator=(BNFAlts const &other)
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
