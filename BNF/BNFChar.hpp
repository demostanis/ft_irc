/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 03:04:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFAlts.hpp"
#include "BNFCat.hpp"
#include "BNFRep.hpp"
#include "BNFString.hpp"
#include "BNFParser.hpp"

class BNFParser;

class BNFChar: public BNFParser
{
	protected:
		char	c;

	public:
					BNFChar(std::string const &name, char c);
					BNFChar(BNFChar const &other);
					~BNFChar(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFAlts		operator|(BNFParser const &other) const;
		BNFAlts     operator|(std::string const &str) const;
		BNFAlts     operator|(char c) const;
		BNFCat		operator&(BNFParser const &other) const;
		BNFCat      operator&(std::string const &str) const;
		BNFCat      operator&(char c) const;
		BNFRep		operator+(size_t max) const;
		BNFRep		operator-(size_t min) const;
		BNFFind		*operator[](std::string const &name) const;
		BNFChar		&operator=(BNFChar const &other);
};
