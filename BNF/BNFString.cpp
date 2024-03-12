/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFString.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:56:04 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFString.hpp"

BNFString::BNFString(std::string const &str, std::string const &name):	BNFParser(name),
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
	if (str.compare(start, this->str.length(), this->str))
	{
		this->errorPos = start;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, this->str.length());
	this->errorPos = BNF_ERROR_POS_NONE;
	return (this->str.length());
}

BNFFind		*BNFString::operator[](std::string const &name) const
{
	BNFFind	*res(new BNFFind());

	if (this->name == name)
		res->pushBack(BNFInher(*this));
	return (res);
}

BNFString	&BNFString::operator=(BNFString const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->str = other.str;
	return (*this);
}
