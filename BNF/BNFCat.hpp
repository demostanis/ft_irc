/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 03:08:14 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFRep.hpp"
#include "BNFString.hpp"
#include "BNFChar.hpp"
#include "BNFParser.hpp"

class BNFCat: public BNFParser
{
	protected:
		std::vector<BNFParser *>	rules;

	public:
					BNFCat(std::string const &name, t_uint count, ...);
					BNFCat(BNFCat const &other);
					~BNFCat(void);
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
		BNFCat		&operator=(BNFCat const &other);
};
