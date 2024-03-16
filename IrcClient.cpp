/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:07:59 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 21:31:25 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"

		IrcClient::IrcClient(): SocketTcpClient(),
								registered(false)
{
}

		IrcClient::IrcClient(SocketTcpClient *client): SocketTcpClient(client->getFd()),
													   registered(false)
{
}

		IrcClient::~IrcClient()
{
}

bool	IrcClient::isRegistered(void) const
{
	return (registered);
}

void	IrcClient::hasRegistered(void)
{
	registered = true;
}
