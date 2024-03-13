/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 01:56:17 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFString.hpp"
#include "BNFChar.hpp"
#include "BNFParser.hpp"

class BNFRep: public BNFParser
{
	protected:
		BNFParser	*rule;
		size_t		min;
		size_t		max;

	public:
					BNFRep(std::string const &name, BNFParser const &rule, size_t min, size_t max);
					BNFRep(BNFRep const &other);
					~BNFRep(void);
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
		BNFRep		&operator=(BNFRep const &other);
};
