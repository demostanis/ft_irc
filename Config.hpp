/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:02 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 18:41:24 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class	Config: public std::map<std::string, std::string>
{
	private:
		static char const	*mandatoryKeys[];
		static BNFVar		kvParser;

	public:
				Config(void);
				Config(std::string const &filename);
		void	read(std::string const &filename);
		bool	contains(std::string const &key);
};
