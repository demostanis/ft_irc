/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:30:22 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/29 22:20:36 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class IrcClient;

class IrcChannel
{
private:
	std::string					name;
	std::vector<IrcClient *>	clients;
	std::string					topic;
	std::string					modes;
	bool						topicForOpsOnly;
	// TODO: handle
	bool						inviteOnly;
	std::string					password;
	int							clientLimit;

public:
		IrcChannel();
		~IrcChannel();

	const std::string				&getName(void) const;
	const std::vector<IrcClient *>	&getClients(void) const;
	void							setName(std::string name);
	void							add(IrcClient *user);
	void							remove(IrcClient *user);
	const std::string				&getTopic(void) const;
	const std::string				&getModes(void) const;
	void							setTopic(std::string name);
	bool							getInviteOnly() const;
	void							setInviteOnly(bool newInviteOnly);
	bool							getTopicForOpsOnly() const;
	void							setTopicForOpsOnly(bool newTopicForOpsOnly);
	void							setPassword(std::string password);
	void							setClientLimit(int n);
	int								getClientLimit() const;
	void							delMode(char mode);
	void							addMode(char mode);
	void							send(IrcClient *client, std::string text);

	static bool				isValidName(std::string name);
};
