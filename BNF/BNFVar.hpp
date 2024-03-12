/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 22:39:22 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFRep.hpp"
#include "BNFParser.hpp"

class BNFVar: public BNFParser
{
	protected:
		BNFParser	*rule;

	public:
					BNFVar(std::string const &name);
					BNFVar(std::string const &name, BNFParser const &rule);
					BNFVar(BNFVar const &other);
					~BNFVar(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFAlts     operator|(BNFParser const &other);
        BNFCat      operator&(BNFParser const &other);
        BNFRep      operator+(size_t max);
        BNFRep      operator-(size_t min);
		BNFFind		*operator[](std::string const &name) const;
		BNFVar		&operator=(BNFVar const &other);
		BNFVar		&operator=(BNFParser const &other);
};
