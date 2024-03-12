/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 19:32:01 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFInher.hpp"
#include "BNFParser.hpp"

class BNFInher;
class BNFParser;

class BNFFind: protected std::vector<BNFInher *>
{
	public:
					BNFFind(void);
					BNFFind(BNFFind const &other);
					~BNFFind(void);
		void		clear(void);
		void		merge(BNFFind &other);
		void		pushBack(BNFInher const &inher);
		void		pushParent(BNFParser const &parent);
		using		std::vector<BNFInher *>::empty;
		using		std::vector<BNFInher *>::size;
		using		std::vector<BNFInher *>::begin;
		using		std::vector<BNFInher *>::end;
		using		std::vector<BNFInher *>::iterator;
		using		std::vector<BNFInher *>::operator[];
		BNFFind		&operator=(BNFFind const &other);
};
