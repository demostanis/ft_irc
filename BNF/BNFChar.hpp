/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:53:36 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFParser.hpp"

class BNFChar: public BNFParser
{
	protected:
		char	c;

	public:
					BNFChar(char c, std::string const &name = BNF_DEFAULT_NAME);
					BNFChar(BNFChar const &other);
					~BNFChar(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFFind		*operator[](std::string const &name) const;
		BNFChar		&operator=(BNFChar const &other);
};
