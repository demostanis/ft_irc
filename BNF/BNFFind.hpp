/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:35:06 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdarg.h>
#include "BNFInher.hpp"
#include "BNFParser.hpp"

class BNFInher;
class BNFParser;

class BNFFind: public std::vector<BNFInher>
{
	public:
					BNFFind(void);
					BNFFind(BNFFind const &other);
					~BNFFind(void);
		void		merge(BNFFind const &other);
		void		pushParent(BNFParser const &parent);
		BNFFind		isHeir(t_uint count, ...) const;
		BNFFind		isFail(void) const;
		BNFFind		isSuccess(void) const;
		BNFFind		&operator=(BNFFind const &other);
};
