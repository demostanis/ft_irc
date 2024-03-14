/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 23:58:08 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFParser.hpp"

class BNFParser;

class BNFInher
{
	protected:
		std::vector<std::string>	inher;
		ssize_t						inherErrorPos;
		std::string					name;
		std::string					value;
		ssize_t						errorPos;

	public:
							BNFInher(BNFParser const &son);
							BNFInher(BNFInher const &other);
							~BNFInher(void);
		size_t				pushParent(BNFParser const &parent);
		bool				isHeir(t_uint count, ...) const;
		bool				isHeir(t_uint count, va_list argList) const;
		std::string const	&getName(void) const;
		std::string const	&getValue(void) const;
		ssize_t				getErrorPos(void) const;
		ssize_t				getInherErrorPos(void) const;
		BNFInher			&operator=(BNFInher const &other);
};
