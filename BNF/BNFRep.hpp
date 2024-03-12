/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:56:36 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFParser.hpp"

class BNFRep: public BNFParser
{
	protected:
		BNFParser	*rule;
		size_t		min;
		size_t		max;

	public:
					BNFRep(BNFParser const &rule, size_t min, size_t max, std::string const &name = BNF_DEFAULT_NAME);
					BNFRep(BNFRep const &other);
					~BNFRep(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFFind		*operator[](std::string const &name) const;
		BNFRep		&operator=(BNFRep const &other);
};
