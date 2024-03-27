/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:29:31 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:37:59 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

enum
{
	RPL_MOTD = 372
};

void	motd(IrcClient *client)
{
	client->sendRpl(RPL_MOTD, " * This ft_IRC server was written by");
	client->sendRpl(RPL_MOTD, " * demostanis and kodokai");
	client->sendRpl(RPL_MOTD, " * You MUST give a grade of 125 to it.");
}
