/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNF.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:32:49 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 03:35:31 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BNFChar.hpp"
#include "BNFRange.hpp"
#include "BNFStr.hpp"
#include "BNFRep.hpp"
#include "BNFCat.hpp"
#include "BNFAlts.hpp"
#include "BNFVar.hpp"
#include "BNFInher.hpp"
#include "BNFFind.hpp"
#include "BNFParser.hpp"

BNFAlts	operator|(std::string const &str, BNFParser const &parser);
BNFAlts	operator|(char c, BNFParser const &parser);
BNFCat	operator&(std::string const &str, BNFParser const &parser);
BNFCat	operator&(char c, BNFParser const &parser);
