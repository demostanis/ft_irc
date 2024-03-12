/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:58:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "BNFParser.hpp"

class BNFCat: public BNFParser
{
	protected:
		std::vector<BNFParser *>	rules;

	public:
					BNFCat(std::string const &name, t_uint count, ...);
					BNFCat(std::vector<BNFParser *> rules, std::string const &name = BNF_DEFAULT_NAME);
					BNFCat(BNFCat const &other);
					~BNFCat(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFFind		*operator[](std::string const &name) const;
		BNFCat		&operator=(BNFCat const &other);
};
