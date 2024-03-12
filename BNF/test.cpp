/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 17:57:01 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFRange.hpp"
#include "BNFString.hpp"
#include "BNFInher.hpp"
#include "BNFCat.hpp"
#include "BNFFind.hpp"
#include "BNFParser.hpp"
#include "BNFChar.hpp"
#include "BNFAlts.hpp"
#include "BNFRep.hpp"

BNFParser	*getParser(void)
{
	BNFChar		zero('0', "zero");
	BNFChar		point('.', "point");
	BNFChar		cl(':', "cl");
	BNFString	ffff("FFFF", "ffff");
	BNFRange	digit('0', '9', "digit");
	BNFRange	hexletter('A', 'F', "hexletter");
	BNFAlts		hexdigit("hexdigit", 2, &digit, &hexletter);
	BNFRep		hexdigits(hexdigit, 1, BNF_INFINI, "hexdigits");
	BNFRep		threeDigit(digit, 1, 3, "threeDigit");
	BNFCat		ip4("ip4", 7, &threeDigit, &point, &threeDigit, &point, &threeDigit, &point, &threeDigit);
	BNFString	ipDualStart("0:0:0:0:0:", "ipDualStart");
	BNFAlts		ipDualMid("ipDualMid", 2, &zero, &ffff);
	BNFCat		ipDual("ipDual", 4, &ipDualStart, &ipDualMid, &cl, &ip4);
	BNFCat		ip6Raw("ip6Raw", 15, &hexdigits, &cl,  &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits);
	BNFAlts		ip6("ip6", 2, &ip6Raw, &ipDual);

	return (ip6.clone());
}

void	findDigit(BNFParser *ip6)
{
	BNFFind::iterator	cr;
	BNFFind				*find;

	find = (*ip6)["hexdigits"];
	for (cr = find->begin(); cr != find->end(); cr++)
	{
		if ((*cr)->getErrorPos() == BNF_ERROR_POS_NONE)
			std::cout << "digit value: " << (*cr)->getValue() << std::endl;
	}
	delete find;
}

int	main(int argc, char *argv[])
{
	BNFParser	*ip6(getParser());

	for (int i = 1; i < argc; i++)
	{
		std::cout << "parser return: " << ip6->parse(argv[i]) << std::endl;
		std::cout << "parse value: " << ip6->getValue() << std::endl;
		std::cout << "parse errorPos: " << ip6->getErrorPos() << std::endl;
		std::cout << std::endl;
		std::cout << "__digit__" << std::endl;
		findDigit(ip6);
		std::cout << std::endl;
		std::cout << std::endl;
	}
	delete ip6;
	return (EXIT_SUCCESS);
}
