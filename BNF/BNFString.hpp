/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFString.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 16:55:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFParser.hpp"

class BNFString: public BNFParser
{
	protected:
		std::string	str;

	public:
					BNFString(std::string const &str, std::string const &name = BNF_DEFAULT_NAME);
					BNFString(BNFString const &other);
					~BNFString(void);
		void		reset(void);
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFFind		*operator[](std::string const &name) const;
		BNFString	&operator=(BNFString const &other);
};
