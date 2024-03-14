/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:39:07 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <stdlib.h>
#include "BNFRep.hpp"

BNFRep::BNFRep(std::string const &name, BNFParser const &rule, size_t min, size_t max):	BNFParser(name),
																						rule(rule.clone()),
																						min(min),
																						max(max)
{
}

BNFRep::BNFRep(BNFParser const &rule, size_t min, size_t max):	BNFParser(kdo::itoa(min) + '*' + kdo::itoa(max) + rule.getFormatName()),
																rule(rule.clone()),
																min(min),
																max(max)
{
}

BNFRep::BNFRep(BNFRep const &other):	BNFParser(other),
										rule(other.rule->clone()),
										min(other.min),
										max(other.max)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
}

BNFRep::~BNFRep(void)
{
	std::vector<BNFParser *>::iterator	cr;

	delete this->rule;
	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
}

std::string	BNFRep::getFormatName(void) const
{
    return (this->name);
}

void		BNFRep::reset(void)
{

	std::vector<BNFParser *>::iterator	cr;

	this->rule->reset();
	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
	this->rules.clear();
	this->value.clear();
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
}

BNFParser	*BNFRep::clone(void) const
{
	return (new BNFRep(*this));
}

ssize_t		BNFRep::parse(std::string const &str, size_t start)
{
	size_t										finalLen(0);
	size_t										count;
	ssize_t										len;
	std::vector<BNFParser *>::const_iterator	cr;

	this->value.clear();
	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
	this->rules.clear();
	for (count = 0; count < this->max; count++)
	{
		len = this->rule->parse(str, start + finalLen);
		this->rules.push_back(rule->clone());
		if (len == BNF_PARSE_ERROR)
			break;
		this->value += this->rule->getValue();
		finalLen += len;	
	}
	if (count < this->min)
	{
		this->value += this->rule->getValue();
		this->errorPos = this->rule->getErrorPos();
		return (BNF_PARSE_ERROR);
	}
	this->errorPos = BNF_ERROR_POS_NONE;
	return (finalLen);
}

BNFAlts		BNFRep::operator|(BNFParser const &other) const
{
	return (BNFAlts(this->getFormatName() + '|' + other.getFormatName(), 2, this, &other));
}

BNFAlts      BNFRep::operator|(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFAlts      BNFRep::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat		BNFRep::operator&(BNFParser const &other) const
{
	return (BNFCat(this->getFormatName() + '&' + other.getFormatName(), 2, this, &other));
}

BNFCat      BNFRep::operator&(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat      BNFRep::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFRep		BNFRep::operator+(size_t max) const
{
	BNFRep		res(*this);

	res.name += '+' + kdo::itoa(max);
	res.max = max;
	return (res);
}

BNFRep		BNFRep::operator-(size_t min) const
{
	BNFRep		res(*this);
	
	res.name += '-' + kdo::itoa(min);
	res.min = min;
	return (res);
}

BNFFind		BNFRep::operator[](std::string const &name) const
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

BNFRep	&BNFRep::operator=(BNFRep const &other)
{
	std::vector<BNFParser *>::const_iterator	cr;

	delete this->rule;
	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	this->rule = other.rule->clone();	
	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
	this->min = other.min;
	this->max = other.max;
	return (*this);
}
