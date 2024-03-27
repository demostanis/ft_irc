/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 10:10:34 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Privmsg, {
	ENSURE_AUTH();

	if (N_PARAMS() == 0)
	{	
		msg.replyError(ERR_NORECIPIENT, ":No recipient given");
		return ;
	}
	if (N_PARAMS() == 1)
	{
		msg.replyError(ERR_NOTEXTTOSEND, ":No text to send");
		return ;
	}

	std::string					targetsRaw = PARAM(0);
	std::vector<std::string>	targets;
	std::string::size_type		pos;

	// TODO: use the BNF parser?
	while ((pos = targetsRaw.find(',')) != std::string::npos)
	{
		std::string	target = targetsRaw.substr(0, pos);
		targets.push_back(target);
		targetsRaw.erase(0, pos + 1);
	}
	if (targets.size() == 0)
		targets.push_back(targetsRaw);

	int	chanlimit;
	kdo::convert(chanlimit, server.getConfig()["chanlimit"]);
	if ((int)targets.size() >= chanlimit)
	{
		msg.replyError(ERR_TOOMANYTARGETS, ":Too many targets");
		return ;
	}

	std::vector<std::string>::iterator	cr = targets.begin();
	for (; cr != targets.end(); ++cr)
	{
		IrcChannel	*channel = server.getChannel(*cr);
		if (channel)
			channel->send(client, PARAM(1));
		else
			msg.replyError(ERR_NOSUCHNICK, ":No such nick/channel");
	}
})
