/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:13:58 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 03:25:07 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNF.hpp"

BNFAlts	operator|(std::string const &str, BNFParser const &parser)
{
	BNFString	tmp(str, str);

	return (BNFAlts(str + "|(" + parser.getName() + ')', 2, &tmp, &parser));
}

BNFAlts	operator|(char c, BNFParser const &parser)
{
	BNFChar	tmp((char[2]){c, '\0'}, c);

	return (BNFAlts(tmp.getName() + "|(" + parser.getName() + ')', 2, &tmp, &parser));
}

BNFCat	operator&(std::string const &str, BNFParser const &parser)
{
	BNFString	tmp(str, str);

	return (BNFCat(str + "|(" + parser.getName() + ')', 2, &tmp, &parser));
}

BNFCat	operator&(char c, BNFParser const &parser)
{

	BNFChar	tmp((char[2]){c, '\0'}, c);

	return (BNFCat(tmp.getName() + "|(" + parser.getName() + ')', 2, &tmp, &parser));
}
