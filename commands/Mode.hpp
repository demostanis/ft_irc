/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:39 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/17 19:36:10 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

typedef enum
{
	plus,
	minus,
}	state;

static void	handleMode(
	IrcChannel *channel, char mode,
	BNFFind	&modeArgs, state modeState
)
{
	switch (mode)
	{
		case 'i':
			channel->setInviteOnly(modeState == plus);
			break ;
		case 't':
			channel->setTopicForOpsOnly(modeState == plus);
			break ;
		case 'k':
			if (modeState == minus)
				channel->setPassword("");
			else if (modeArgs.size() > 0 &&
				modeArgs[0].find(' ') == std::string::npos)
			{
				channel->setPassword(modeArgs[0].string());
				modeArgs.erase(modeArgs.begin());
			}
			else
				// TODO: error?
				;
			break ;
		case 'l':
			if (modeState == minus)
				channel->setClientLimit(-1);
			else if (modeArgs.size() > 0)
			{
				int clientLimit;
				if (kdo::convert(clientLimit, modeArgs[0]))
					channel->setClientLimit(clientLimit);
				modeArgs.erase(modeArgs.begin());
			}
			else
				// TODO: error?
			break ;
	}
	if (modeState == plus)
		channel->addMode(mode);
	else
		channel->delMode(mode);
}

DEFINE_CMD(Mode, {
	ENSURE_AUTH();

	if (N_PARAMS() < 1)
	{
		msg.replyError(ERR_NEEDMOREPARAMS, ":Not enough parameters");
		return ;
	}

	std::string	param = PARAM(0);
	if (param[0] == '#')
	{
		if (server.channelExists(param))
		{
			if (N_PARAMS() == 1)
				client->sendRpl(RPL_CHANNELMODEIS, param + " +" +
					server.getChannel(param)->getModes());
			else
			{
				std::string		modes = PARAM(1);
				std::string		modeArgsRaw;
				BNFFind			modeArgs;
				state			modeState;

				if (N_PARAMS() >= 3)
				{
					modeArgsRaw = PARAM(2);
					listParser.parse(modeArgsRaw);
					modeArgs = listParser["word"];
				}
				if (modes[0] != '+' && modes[0] != '-')
					return ;
				for (size_t i = 0; i < modes.length(); i++)
				{
					char	mode = modes[i];

					if (mode == '+')
						modeState = plus;
					else if (mode == '-')
						modeState = minus;
					else if (std::string("itkol").find(mode) != std::string::npos)
						handleMode(server.getChannel(param), mode, modeArgs, modeState);
					else
						msg.replyError(ERR_UMODEUNKNOWNFLAG, "Unknown MODE flag");
				}
			}
		}
		else
			msg.replyError(ERR_NOSUCHCHANNEL, ":No such channel");
	}
	else
	{
		if (client->getNick() != param)
		{
			msg.replyError(ERR_USERSDONTMATCH, ":Can't change mode for other users");
			return ;
		}
		if (N_PARAMS() == 1)
			client->sendRpl(RPL_UMODEIS, "+" + client->getModes());
		else
		{
			if (PARAM(1).find('o') != std::string::npos)
			{
				if (PARAM(1)[0] == '+')
					client->addMode('o');
				else if (PARAM(1)[0] == '-')
					client->delMode('o');
			}
		}
	}
})
