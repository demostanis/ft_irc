/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNF.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:13:58 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 14:20:55 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNF.hpp"

BNFAlts	operator|(std::string const &str, BNFParser const &parser)
{
	BNFStr	tmp(str);

	return (BNFAlts(2, &tmp, &parser));
}

BNFAlts	operator|(char c, BNFParser const &parser)
{
	BNFChar	tmp(c);

	return (BNFAlts(2, &tmp, &parser));
}

BNFCat	operator&(std::string const &str, BNFParser const &parser)
{
	BNFStr	tmp(str);

	return (BNFCat(2, &tmp, &parser));
}

BNFCat	operator&(char c, BNFParser const &parser)
{

	BNFChar	tmp(c);

	return (BNFCat(2, &tmp, &parser));
}
