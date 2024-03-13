/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/13 03:49:12 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNF.hpp"

//BNFParser	*getParser(void)
//{
//	BNFChar		zero("zero", '0');
//	BNFChar		point("point", '.');
//	BNFChar		cl("cl", ':');
//	BNFString	ffff("ffff", "FFFF");
//	BNFRange	digit("digit", '0', '9');
//	BNFRange	hexletter("hexletter", 'A', 'F');
//	BNFAlts		hexdigit("hexdigit", 2, &digit, &hexletter);
//	BNFRep		hexdigits("hexdigits", hexdigit, 1, BNF_INFINI);
//	BNFRep		threeDigit("threeDigit", digit, 1, 3);
//	BNFCat		ip4("ip4", 7, &threeDigit, &point, &threeDigit, &point, &threeDigit, &point, &threeDigit);
//	BNFString	ipDualStart("0:0:0:0:0:", "ipDualStart");
//	BNFAlts		ipDualMid("ipDualMid", 2, &zero, &ffff);
//	BNFCat		ipDual("ipDual", 4, &ipDualStart, &ipDualMid, &cl, &ip4);
//	BNFCat		ip6Raw("ip6Raw", 15, &hexdigits, &cl,  &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits, &cl, &hexdigits);
//	BNFAlts		ip6("ip6", 2, &ip6Raw, &ipDual);
//
//	return (ip6.clone());
//}

BNFVar	getParser(void)
{
	BNFChar		zero("zero", '0');
	BNFChar		point("point", '.');
	BNFChar		cl("cl", ':');
	BNFRange	digit("digit", '0', '9');
	BNFRange	hexletter("hexletter", 'A', 'F');
	BNFVar		hexdigit("hexdigit");
	BNFVar		ip4("ip4");
	BNFVar		ip6("ip6");

	hexdigit = digit | hexletter;
	ip4 = digit - 1 + 3 & point & digit - 1 + 3 & point & digit - 1 + 3 & point & digit - 1 + 3;
	ip6 = (hexdigit - 1 & (cl & hexdigit - 1) - 7 + 7)
		| ("0:0:0:0:0:" & (zero | "FFFF") & cl & ip4);

	return (ip6);
}

void	findDigit(BNFParser &ip6)
{
	BNFFind::iterator	cr;
	BNFFind				*find;

	find = ip6["ip4"];
	std::cout << find->size() << std::endl;
	for (cr = find->begin(); cr != find->end(); cr++)
	{
		std::cout << "digit value: " << (*cr)->getValue() << std::endl;
	}
	delete find;
}

int	main(int argc, char *argv[])
{
	BNFVar	ip6(getParser());

	for (int i = 1; i < argc; i++)
	{
		std::cout << "parser return: " << ip6.parse(argv[i]) << std::endl;
		std::cout << "parse value: " << ip6.getValue() << std::endl;
		std::cout << "parse errorPos: " << ip6.getErrorPos() << std::endl;
		std::cout << std::endl;
		std::cout << "__digit__" << std::endl;
		findDigit(ip6);
		std::cout << std::endl;
		std::cout << std::endl;
	}
	return (EXIT_SUCCESS);
}
