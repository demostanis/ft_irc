/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/21 01:32:58 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

static void	sendNames(IrcClient *client, IrcChannel &channel)
{
	std::vector<IrcClient *>::const_iterator	cr = channel.getClients().begin();
	std::string	usernames = "";

	for (; cr != channel.getClients().end(); ++cr)
	{
		// TODO: add @ if op
		usernames += "@" + (*cr)->getNick();
		if (cr != channel.getClients().end() - 1)
			usernames += " ";
	}
	client->sendRpl(RPL_NAMREPLY, "= " + channel.getName() + " :" + usernames);
	client->sendRpl(RPL_ENDOFNAMES, channel.getName() + " :End of /NAMES list");
}

void	Join::handle(IrcServer &server, IrcMessage &msg)
{
	IrcClient	*client	= msg.getClient();
	std::string	channelName;
	IrcChannel	*channel;

	if (!client || !client->isRegistered())
	{
		msg.replyError(ERR_NOTREGISTERED, ":You have not registered");
		return ;
	}
	if (msg.getParams().size() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	channelName = msg.getParams()[0].getValue();
	if (!IrcChannel::isValidName(channelName))
	{
		msg.replyError(ERR_BADCHANNAME, ":Illegal channel name");
		return ;
	}
	channel = server.createChannelIfNeeded(channelName);
	channel->add(client);
	client->addChannel(channel);
	// such an odd packet
	client->send(
		":" + client->getNick() +
		" JOIN " + channelName + CRLF
		, MSG_DONTWAIT);
	if (!channel->getTopic().empty())
		client->sendRpl(RPL_TOPIC, channelName + " :" + channel->getTopic());
	sendNames(client, *channel);
}
