/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:11:19 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/16 21:36:36 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IrcMessage.hpp"
#include <iostream>

class Nick
{
public:
	static void	handle(IrcMessage &msg);
};
