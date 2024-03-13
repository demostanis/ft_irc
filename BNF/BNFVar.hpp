/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 15:12:31 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFRep.hpp"
#include "BNFString.hpp"
#include "BNFChar.hpp"
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
		std::string getFormatName(void) const;
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFAlts     operator|(BNFParser const &other) const;
		BNFAlts     operator|(std::string const &str) const;
		BNFAlts     operator|(char c) const;
        BNFCat      operator&(BNFParser const &other) const;
		BNFCat      operator&(std::string const &str) const;
		BNFCat      operator&(char c) const;
        BNFRep      operator+(size_t max) const;
        BNFRep      operator-(size_t min) const;
		BNFFind		*operator[](std::string const &name) const;
		BNFVar		&operator=(BNFVar const &other);
		BNFVar		&operator=(BNFParser const &other);
};
