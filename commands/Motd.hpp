/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Motd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:11:19 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 22:28:27 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../irc.hpp"

#define RPL_MOTD 372

class Motd
{
	public:
		static void	handle(IrcServer &server, IrcMessage &msg);
		static void	doIt(IrcClient *client);
};
