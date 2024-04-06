/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:44:19 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/06 02:06:35 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	quit(IrcClient *client, std::string reason)
{
	ITER_CLIENT_CHANNELS(client)
	{
		if (CHANNEL() != NULL)
		{
			ITER_CHANNEL_CLIENTS(*CHANNEL())
			{
				if (CLIENT() != client)
					CLIENT()->sendRaw(":" + client->getIdentifier() +
						" QUIT :" + reason);
			}
			CHANNEL()->remove(client);
		}
	}
}
