/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:13:58 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 15:22:35 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNF.hpp"

BNFAlts	operator|(std::string const &str, BNFParser const &parser)
{
	BNFString	tmp(str);

	return (BNFAlts(tmp.getFormatName() + '|' + parser.getFormatName(), 2, &tmp, &parser));
}

BNFAlts	operator|(char c, BNFParser const &parser)
{
	BNFChar	tmp(c);

	return (BNFAlts(tmp.getFormatName() + '|' + parser.getFormatName(), 2, &tmp, &parser));
}

BNFCat	operator&(std::string const &str, BNFParser const &parser)
{
	BNFString	tmp(str);

	return (BNFCat(tmp.getFormatName() + '|' + parser.getFormatName(), 2, &tmp, &parser));
}

BNFCat	operator&(char c, BNFParser const &parser)
{

	BNFChar	tmp(c);

	return (BNFCat(tmp.getFormatName() + '|' + parser.getFormatName(), 2, &tmp, &parser));
}
