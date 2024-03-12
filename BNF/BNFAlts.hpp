/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:57:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdarg.h"
#include "BNFParser.hpp"

class BNFAlts: public BNFParser
{
	protected:
		std::vector<BNFParser *>	rules;

	public:
					BNFAlts(std::string const &name, t_uint count, ...);
					BNFAlts(std::vector<BNFParser *> rules, std::string const &name = BNF_DEFAULT_NAME);
					BNFAlts(BNFAlts const &other);
					~BNFAlts(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFFind		*operator[](std::string const &name) const;
		BNFAlts		&operator=(BNFAlts const &other);
};
