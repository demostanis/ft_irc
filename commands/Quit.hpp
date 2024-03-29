/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 21:51:34 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

namespace Quit
{
	void	doIt(IrcServer &server, IrcClient *client, std::string reason)
	{
		ITER_CLIENT_CHANNELS(client)
		{
			if (CHANNEL() != NULL)
			{
				ITER_CHANNEL_CLIENTS(*CHANNEL())
				{
					if (CLIENT() != client)
						CLIENT()->sendRaw(":" + client->getNick() +
							" QUIT :" + reason);
				}
			}
		}
		// TODO: client->disconnect()
		server.disconnectClient(client->getFd());
	}
}

DEFINE_CMD(Quit, {
	IrcClient		*client = msg.getClient();
	std::string		reason;

	if (N_PARAMS() > 0)
		reason = PARAM(0);
	Quit::doIt(server, client, reason);
})
