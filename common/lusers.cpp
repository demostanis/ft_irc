/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lusers.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:31:31 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:37:38 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

enum
{
	RPL_LUSERCLIENT = 251,
	RPL_LUSERME = 255,
};

void	lusers(IrcServer &server, IrcClient *client)
{
	std::string	count;

	kdo::convert(count, server.userCount());
	client->sendRpl(RPL_LUSERCLIENT, "There are " + count + " users on 1 server");
	client->sendRpl(RPL_LUSERME, "I have " + count + " users and 1 server");
}
