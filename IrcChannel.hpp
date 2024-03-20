/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:30:22 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/20 03:13:52 by cgodard          ###   ########.fr       */
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

public:
		IrcChannel();
		~IrcChannel();

	const std::string				&getName(void) const;
	const std::vector<IrcClient *>	&getClients(void) const;
	void							setName(std::string name);
	void							add(IrcClient *user);
	const std::string				&getTopic(void) const;
	void							setTopic(std::string name);

	static bool				isValidName(std::string name);
};
