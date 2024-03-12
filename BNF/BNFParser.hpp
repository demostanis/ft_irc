/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 21:52:42 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <stdarg.h>
#include "../kdolib/kdolib.hpp"
#include "BNFFind.hpp"

#define BNF_INFINI					SIZE_MAX
#define BNF_PARSE_ERROR				-1
#define BNF_ERROR_POS_NONE			-1
#define BNF_ERROR_POS_UNINITIALIZED	SSIZE_MAX

class BNFFind;
class BNFAlts;
class BNFCat;
class BNFRep;

class BNFParser
{
	protected:
		std::string	name;
		std::string	value;
		ssize_t		errorPos;

	public:
							BNFParser(std::string const &name);
							BNFParser(BNFParser const &other);
		virtual				~BNFParser(void);
		std::string const	&getName(void) const;
		std::string const	&getValue(void) const;
		ssize_t				getErrorPos(void) const;
		virtual void		reset(void) = 0;
		virtual BNFParser	*clone(void) const = 0;
		virtual ssize_t		parse(std::string const &str, size_t start = 0) = 0;
		virtual BNFFind		*operator[](std::string const &name) const = 0;
		virtual BNFAlts		operator|(BNFParser const &other) = 0;
		virtual BNFCat		operator&(BNFParser const &other) = 0;
		virtual BNFRep		operator+(size_t max) = 0;
		virtual BNFRep		operator-(size_t min) = 0;
		BNFParser			&operator=(BNFParser const &other);
};
