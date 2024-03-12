/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 00:39:56 by nlaerema         ###   ########.fr       */
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

BNFAlts     BNFAlts::operator|(BNFParser const &other)
{
	BNFAlts	res(*this);

	res.name += '|' + other.getName();
	res.rules.push_back(other.clone());
	return (res);
}

BNFCat		BNFAlts::operator&(BNFParser const &other)
{
	return (BNFCat('(' + this->name + ")&(" + other.getName() + ')', 2, this, &other));
}

BNFRep      BNFAlts::operator+(size_t max)
{
	std::string     maxStr;

	kdo::convert(maxStr, max);
	return (BNFRep('(' + this->name + ")+" + maxStr, *this, 0, max));
}

BNFRep      BNFAlts::operator-(size_t min)
{
	std::string     minStr;
	
	kdo::convert(minStr, min);
	return (BNFRep('(' + this->name + ")-" + minStr, *this, min, BNF_INFINI));
}

BNFFind		*BNFAlts::operator[](std::string const &name) const
{
	std::vector<BNFParser *>::const_iterator	cr;
	BNFFind										*finalRes(new BNFFind());
	BNFFind										*res;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
	{
		res = (**cr)[name];
		finalRes->merge(*res);
		delete res;
	}
	finalRes->pushParent(*this);
	if (this->name == name)
		finalRes->pushBack(BNFInher(*this));
	return (finalRes);
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
