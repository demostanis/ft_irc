/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/21 00:13:41 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg.hpp"

void	Privmsg::handle(IrcServer &server, IrcMessage &msg)
{
	IrcClient	*client	= msg.getClient();

	(void)server;
	if (!client || !client->isRegistered())
	{
		msg.replyError(ERR_NOTREGISTERED, ":You have not registered");
		return ;
	}
	if (msg.getParams().size() == 0)
	{	
		msg.replyError(ERR_NORECIPIENT, ":No recipient given");
		return ;
	}
	if (msg.getParams().size() == 1)
	{
		msg.replyError(ERR_NOTEXTTOSEND, ":No text to send");
		return ;
	}

	std::string					targetsRaw = msg.getParams()[0].getValue();
	std::vector<std::string>	targets;
	std::string::size_type		pos;

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
			channel->send(client, msg.getParams()[1].getValue());
		else
			msg.replyError(ERR_NOSUCHNICK, ":No such nick/channel");
	}
}
