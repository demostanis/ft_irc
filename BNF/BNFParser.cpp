/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 10:49:41 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFParser.hpp"

BNFParser::BNFParser(std::string const &name):	name(name),
												errorPos(BNF_ERROR_POS_UNINITIALIZED)
{
}

BNFParser::BNFParser(BNFParser const &other):	name(other.name),
												value(other.value),
												errorPos(other.errorPos)
{
}

BNFParser::~BNFParser(void)
{
}

std::string const	&BNFParser::getName(void) const
{
	return (this->name);
}

std::string const	&BNFParser::getValue(void) const
{
	return (this->value);
}

ssize_t				BNFParser::getErrorPos(void) const
{
	return (this->errorPos);
}

BNFParser			&BNFParser::operator=(BNFParser const &other)
{
	this->name = other.name;
	this->value = other.value;
	this->errorPos = other.errorPos;
	return (*this);
}
