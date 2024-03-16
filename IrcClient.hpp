/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:06:54 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 21:44:39 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SocketTcpClient.hpp"

class IrcClient: public SocketTcpClient
{
private:
	bool				registered;
	std::string			nick;

public:
			IrcClient();
			IrcClient(SocketTcpClient *client);
			~IrcClient();

	bool				isRegistered(void) const;
	void				hasRegistered();
	void				setNick(const std::string &nick);
	const std::string	&getNick() const;
};
