/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 15:06:23 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFFind.hpp"

BNFFind::BNFFind(void)
{
}

BNFFind::BNFFind(BNFFind const &other)
{
	std::vector<BNFInher *>::const_iterator	cr;

	for (cr = other.begin(); cr != other.end(); cr++)
		this->pushBack(**cr);
}

BNFFind::~BNFFind(void)
{
	std::vector<BNFInher *>::iterator	cr;

	for (cr = this->begin(); cr != this->end(); cr++)
		delete *cr;
}

void		BNFFind::clear(void)
{
	std::vector<BNFInher *>::iterator	cr;

	for (cr = this->begin(); cr != this->end(); cr++)
		delete *cr;
	this->std::vector<BNFInher *>::clear();
}

void		BNFFind::pushBack(BNFInher const &inher)
{
	this->push_back(new BNFInher(inher));
}

void		BNFFind::merge(BNFFind &other)
{
	std::vector<BNFInher *>::iterator	end(other.end());
	std::vector<BNFInher *>::iterator	cr;

	for (cr = other.begin(); cr != end; cr++)
		this->push_back(*cr);
	other.std::vector<BNFInher *>::clear();
}

void		BNFFind::pushParent(BNFParser const &parent)
{
	std::vector<BNFInher *>::iterator	cr;

	for (cr = this->begin(); cr != this->end(); cr++)
		(*cr)->pushParent(parent);
}

BNFFind		&BNFFind::operator=(BNFFind const &other)
{
	std::vector<BNFInher *>::const_iterator	cr;

	this->clear();
	for (cr = other.begin(); cr != other.end(); cr++)
		this->pushBack(**cr);
	return (*this);
}
