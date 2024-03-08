/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:52:40 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/08 09:51:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mitm.hpp"

int	main(void)
{
	Mitm		mitm;
	std::string addr;
	std::string inPort;
	std::string outPort;

	kdo::userinput("server ip: ", addr);
	kdo::userinput("in port: ", inPort);
	kdo::userinput("out port: ", outPort);
	if (mitm.connect(addr, inPort, outPort))
		return (EXIT_FAILURE);
	mitm.loop();
}
