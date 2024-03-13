/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 15:35:59 by nlaerema         ###   ########.fr       */
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
}

BNFRep::~BNFRep(void)
{
	delete this->rule;
}

std::string	BNFRep::getFormatName(void) const
{
    return (this->name);
}

void		BNFRep::reset(void)
{
	this->rule->reset();
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
	this->value.clear();
}

BNFParser	*BNFRep::clone(void) const
{
	return (new BNFRep(*this));
}

ssize_t		BNFRep::parse(std::string const &str, size_t start)
{
	size_t	finalLen(0);
	t_uint	cr;
	ssize_t	len;

	this->value.clear();
	for (cr = 0; cr < this->max; cr++)
	{
		len = this->rule->parse(str, start + finalLen);
		this->value += this->rule->getValue();
		if (len == BNF_PARSE_ERROR)
			break;
		finalLen += len;	
	}
	if (cr < this->min)
	{
		this->errorPos = start + finalLen;
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

BNFFind		*BNFRep::operator[](std::string const &name) const
{
	BNFFind	*finalRes(new BNFFind());
	BNFFind	*res;

	res = (*this->rule)[name];
	finalRes->merge(*res);
	delete res;
	finalRes->pushParent(*this);
	if (this->name == name)
		finalRes->pushBack(BNFInher(*this));
	return (finalRes);
}

BNFRep	&BNFRep::operator=(BNFRep const &other)
{
	delete this->rule;
	*static_cast<BNFParser *>(this) = other;
	this->rule = other.rule->clone();	
	this->min = other.min;
	this->max = other.max;
	return (*this);
}
