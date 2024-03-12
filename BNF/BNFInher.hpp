/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 17:54:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <stdarg.h>
#include "BNFParser.hpp"
#include "../kdolib/kdolib.hpp"

class BNFParser;

class BNFInher
{
	protected:
		std::vector<std::string>	inheritance;
		std::string					name;
		std::string					value;
		ssize_t						errorPos;

	public:
							BNFInher(BNFParser const &son);
							~BNFInher(void);
		size_t				pushParent(BNFParser const &parent);
		bool				isHeir(t_uint count, ...) const;
		std::string const	&getName(void) const;
		std::string const	&getValue(void) const;
		ssize_t				getErrorPos(void) const;
};
