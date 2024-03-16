/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 21:34:32 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/Pass.hpp"
#include "Config.hpp"

extern Config	config;

		Pass::Pass()
{
}

		Pass::~Pass()
{
}

void	Pass::handle(IrcMessage &msg)
{
	if (msg.getParams().size() == 0)
		msg.replyError(ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
	else
	{
		std::string	password = msg.getParams()[0].getValue();
		IrcClient	*client	= msg.getClient();

		// TODO: should be argv[1] instead of config.password
		if (password == config.password)
		{
			if (client)
			{
				if (client->isRegistered())
					msg.replyError(ERR_ALREADYREGISTERED, ":You may not reregister");
				else
					client->hasRegistered();
			}
		}
		else
			msg.replyError(ERR_PASSWDMISMATCH, ":Password incorrect");
	}
}
