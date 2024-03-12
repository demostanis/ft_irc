/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 23:42:41 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFVar.hpp"

BNFVar::BNFVar(std::string const &name):	BNFParser(name),
											rule(NULL)
{
}

BNFVar::BNFVar(std::string const &name, BNFParser const &rule):	BNFParser(name),
																rule(rule.clone())
{
}

BNFVar::BNFVar(BNFVar const &other):	BNFParser(other),
										rule(other.rule->clone())
{
}

BNFVar::~BNFVar(void)
{
	delete this->rule;
}

void		BNFVar::reset(void)
{
	this->rule->reset();
	this->value = this->rule->getValue();
	this->errorPos = this->rule->getErrorPos();
}

BNFParser	*BNFVar::clone(void) const
{
	return (new BNFVar(*this));
}

ssize_t		BNFVar::parse(std::string const &str, size_t start)
{
	ssize_t	res;

	res = this->rule->parse(str, start);
	this->value = this->rule->getValue();
	this->errorPos = this->rule->getErrorPos();
	return(res);
}

BNFAlts     BNFVar::operator|(BNFParser const &other)
{
        return (BNFAlts(this->name + "|(" + other.getName() + ')', 2, this, &other));
}

BNFCat      BNFVar::operator&(BNFParser const &other)
{
        return (BNFCat(this->name + "&(" + other.getName() + ')', 2, this, &other));
}

BNFRep      BNFVar::operator+(size_t max)
{
        std::string     maxStr;

        kdo::convert(maxStr, max);
        return (BNFRep(this->name + '+' + maxStr, *this, 0, max));
}

BNFRep		BNFVar::operator-(size_t min)
{
        std::string     minStr;

        kdo::convert(minStr, min);
        return (BNFRep(this->name + '-' + minStr, *this, min, BNF_INFINI));
}

BNFFind		*BNFVar::operator[](std::string const &name) const
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

BNFVar	&BNFVar::operator=(BNFVar const &other)
{
	delete this->rule;
	this->value = other.getValue();
	this->errorPos = other.getErrorPos();
	this->rule = other.rule->clone();
	return (*this);
}

BNFVar	&BNFVar::operator=(BNFParser const &other)
{
	delete this->rule;
	this->value = other.getValue();
	this->errorPos = other.getErrorPos();
	this->rule = other.clone();
	return (*this);
}
