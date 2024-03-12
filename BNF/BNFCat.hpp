/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 22:35:34 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFRep.hpp"
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
		BNFAlts     operator|(BNFParser const &other);
        BNFCat      operator&(BNFParser const &other);
        BNFRep      operator+(size_t max);
        BNFRep      operator-(size_t min);
		BNFFind		*operator[](std::string const &name) const;
		BNFCat		&operator=(BNFCat const &other);
};
