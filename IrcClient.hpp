/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:06:54 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 21:32:17 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SocketTcpClient.hpp"

class IrcClient: public SocketTcpClient
{
private:
	bool	registered;

public:
			IrcClient();
			IrcClient(SocketTcpClient *client);
			~IrcClient();

	bool	isRegistered(void) const;
	void	hasRegistered();
};
