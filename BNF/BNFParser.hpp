/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:53:01 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "BNFFind.hpp"
#include "../kdolib/kdolib.hpp"

#define BNF_INFINI					SIZE_MAX
#define BNF_PARSE_ERROR				-1
#define BNF_ERROR_POS_NONE			-1
#define BNF_ERROR_POS_UNINITIALIZED	SSIZE_MAX
#define BNF_DEFAULT_NAME			""

class BNFFind;

class BNFParser
{
	protected:
		std::string	name;
		std::string	value;
		ssize_t		errorPos;

	public:
							BNFParser(std::string const &name = BNF_DEFAULT_NAME);
							BNFParser(BNFParser const &other);
		virtual				~BNFParser(void);
		std::string const	&getName(void) const;
		std::string const	&getValue(void) const;
		ssize_t				getErrorPos(void) const;
		virtual void		reset(void) = 0;
		virtual BNFParser	*clone(void) const = 0;
		virtual ssize_t		parse(std::string const &str, size_t start = 0) = 0;
		virtual BNFFind		*operator[](std::string const &name) const = 0;
		BNFParser			&operator=(BNFParser const &other);
};
