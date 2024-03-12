/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:57:04 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFRep.hpp"

BNFRep::BNFRep(BNFParser const &rule, size_t min, size_t max, std::string const &name):	BNFParser(name),
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
	for (cr = 0; cr < this->max && start + finalLen < str.length(); cr++)
	{
		len = this->rule->parse(str, start + finalLen);
		if (len == BNF_PARSE_ERROR)
			break;
		this->value += this->rule->getValue();
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

BNFFind		*BNFRep::operator[](std::string const &name) const
{
	std::vector<BNFParser *>::const_iterator	cr;
	BNFFind										*finalRes(new BNFFind());
	BNFFind										*res;

	res = (*this->rule)[name];
	finalRes->merge(*res);
	delete res;
	finalRes->pushParent(*this);
	if (this->name == name)
		finalRes->pushBack(BNFInher(*this));
	return (finalRes);
}

BNFRep::~BNFRep(void)
{
	delete this->rule;
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
