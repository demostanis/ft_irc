/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 01:13:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFInher.hpp"

BNFInher::BNFInher(BNFParser const &son):	inherErrorPos(BNF_ERROR_POS_NONE),
											name(son.getName()),
											value(son.getValue()),
											errorPos(son.getErrorPos())
{
}


BNFInher::BNFInher(BNFInher const &other):	inher(other.inher),
											inherErrorPos(other.inherErrorPos),
											name(other.name),
											value(other.value),
											errorPos(other.errorPos)
{
}

BNFInher::~BNFInher(void)
{
}

size_t				BNFInher::pushParent(BNFParser const &parent)
{
	this->inher.push_back(parent.getName());
	this->inherErrorPos = std::max(this->inherErrorPos, parent.getErrorPos());
	return (this->inher.size());
}

bool				BNFInher::isHeir(t_uint count, ...) const
{
	va_list	argList;

	va_start(argList, count);
	return (this->isHeir(count, argList));
}

bool				BNFInher::isHeir(t_uint count, va_list argList) const
{
	std::vector<std::string>::const_iterator	cr;
	char										*parent;

	cr = this->inher.begin();
	while (cr != this->inher.end() && count)
	{
		parent = va_arg(argList, char *);
		while (cr != this->inher.end() && *cr != parent)
			cr++;
		count--;
	}
	va_end(argList);
	if (cr == this->inher.end())
		return (false);	
	return (true);
}

std::string const	&BNFInher::getName(void) const
{
	return (this->name);
}

std::string const	&BNFInher::getValue(void) const
{
	return (this->value);
}

ssize_t				BNFInher::getErrorPos(void) const
{
	return (this->errorPos);
}

ssize_t				BNFInher::getInherErrorPos(void) const
{
	return (this->inherErrorPos);
}

BNFInher			&BNFInher::operator=(BNFInher const &other)
{
	this->inher = other.inher;
	this->inherErrorPos = other.inherErrorPos;
	this->name = other.name;
	this->value = other.value;
	this->errorPos = other.errorPos;
	return (*this);
}
