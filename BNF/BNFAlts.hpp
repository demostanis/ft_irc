/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 01:51:56 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFCat.hpp"
#include "BNFRep.hpp"
#include "BNFString.hpp"
#include "BNFChar.hpp"
#include "BNFParser.hpp"

class BNFParser;

class BNFAlts: public BNFParser
{
	protected:
		std::vector<BNFParser *>	rules;

	public:
					BNFAlts(std::string const &name, t_uint count, ...);
					BNFAlts(BNFAlts const &other);
					~BNFAlts(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFAlts     operator|(BNFParser const &other);
		BNFAlts     operator|(std::string const &str);
		BNFAlts     operator|(char c);
        BNFCat      operator&(BNFParser const &other);
		BNFCat      operator&(std::string const &str);
		BNFCat      operator&(char c);
        BNFRep      operator+(size_t max);
        BNFRep      operator-(size_t min);
		BNFFind		*operator[](std::string const &name) const;
		BNFAlts		&operator=(BNFAlts const &other);
};
