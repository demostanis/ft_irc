/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lusers.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:11:19 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 22:23:45 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../irc.hpp"

#define RPL_LUSERCLIENT 251
#define RPL_LUSERME 255

class Lusers
{
	public:
		static void	handle(IrcServer &server, IrcMessage &msg);
		static void	doIt(IrcServer &server, IrcClient *client);
};
