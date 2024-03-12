/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 17:58:07 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFInher.hpp"

BNFInher::BNFInher(BNFParser const &son):	name(son.getName()),
											value(son.getValue()),
											errorPos(son.getErrorPos())
{
}

BNFInher::~BNFInher(void)
{
}

size_t				BNFInher::pushParent(BNFParser const &parent)
{
	this->inheritance.push_back(parent.getName());
	return (this->inheritance.size());
}

bool				BNFInher::isHeir(t_uint count, ...) const
{
	std::vector<std::string>::const_iterator	cr;
	char										*parent;
	va_list										argList;

	va_start(argList, count);
	cr = this->inheritance.begin();
	while (cr != this->inheritance.end() && count)
	{
		parent = va_arg(argList, char *);
		while (cr != this->inheritance.end() && *cr != parent)
			cr++;
		count--;
	}
	va_end(argList);
	if (cr == this->inheritance.end())
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
