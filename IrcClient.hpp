/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:06:54 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/18 01:36:50 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "kdolib/kdolib.hpp"

class IrcClient: public SocketTcpClient
{
private:
	bool				registered;
	bool				hasGivenPassword;
	std::string			nick;
	std::string			username;
	std::string			realname;

public:
						IrcClient(void);
						IrcClient(int socketConnected);
						~IrcClient(void);
	bool				isRegistered(void) const;
	void				sendRpl(int rpl, std::string msg) const;
	void				hasRegistered(void);
	void				setHasGivenPassword(void);
	bool				getHasGivenPassword(void) const;
	void				setNick(const std::string &nick);
	void				setIdentity(const std::string &username, const std::string &realname);
	const std::string	&getNick() const;
};
