/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFString.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 02:05:28 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFRep.hpp"
#include "BNFChar.hpp"
#include "BNFParser.hpp"

class BNFString: public BNFParser
{
	protected:
		std::string	str;

	public:
					BNFString(std::string const &name, std::string const &str);
					BNFString(BNFString const &other);
					~BNFString(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFAlts		operator|(BNFParser const &other);
		BNFAlts     operator|(std::string const &str);
		BNFAlts     operator|(char c);
        BNFCat      operator&(BNFParser const &other);
		BNFCat      operator&(std::string const &str);
		BNFCat      operator&(char c);
        BNFRep      operator+(size_t max);
        BNFRep      operator-(size_t min);
		BNFFind		*operator[](std::string const &name) const;
		BNFString	&operator=(BNFString const &other);
};
