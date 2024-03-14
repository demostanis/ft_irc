/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 01:14:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFFind.hpp"

BNFFind::BNFFind(void)
{
}

BNFFind::BNFFind(BNFFind const &other): std::vector<BNFInher>(other)
{
}

BNFFind::~BNFFind(void)
{
}

void		BNFFind::merge(BNFFind const &other)
{
	BNFFind::const_iterator	cr;

	for (cr = other.begin(); cr != other.end(); cr++)
		this->push_back(*cr);
}

BNFFind		BNFFind::isHeir(t_uint count, ...) const
{
	va_list					argList;
	va_list					argListCopy;
	BNFFind					res;
	BNFFind::const_iterator	cr;

	va_start(argList, count);
	for (cr = this->begin(); cr != this->end(); cr++)
	{
		__builtin_va_copy(argListCopy, argList);
		if ((*cr).isHeir(count, argListCopy))
			res.push_back(*cr);
	}
	va_end(argList);
	return (res);
}

BNFFind		BNFFind::isFail(void) const
{
	BNFFind					res;
	BNFFind::const_iterator	cr;

	for (cr = this->begin(); cr != this->end(); cr++)
	{
		if ((*cr).getInherErrorPos() != BNF_ERROR_POS_NONE)
			res.push_back(*cr);
	}
	return (res);
}

BNFFind		BNFFind::isSuccess(void) const
{
	BNFFind					res;
	BNFFind::const_iterator	cr;

	for (cr = this->begin(); cr != this->end(); cr++)
	{
		if ((*cr).getInherErrorPos() == BNF_ERROR_POS_NONE)
			res.push_back(*cr);
	}
	return (res);
}

void		BNFFind::pushParent(BNFParser const &parent)
{
	BNFFind::iterator	cr;

	for (cr = this->begin(); cr != this->end(); cr++)
		(*cr).pushParent(parent);
}

BNFFind		&BNFFind::operator=(BNFFind const &other)
{
	*static_cast<std::vector<BNFInher> *>(this) = other;
	return (*this);
}
