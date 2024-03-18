/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:02 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/18 00:50:20 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "Exceptions.hpp"

static const std::string	allowedKeys[] = {
	"admin",
	"prefix",
	"password",
};

class	Config
{
	private:
		typedef std::map<std::string, std::string>	kvT;
		kvT											kv;

	public:
		Config();
		~Config();

		DEFINE_EXCEPTION(Parse);
		DEFINE_EXCEPTION(Missing);

		template <typename T>
		std::pair<bool, T>	get(std::string key) const
		{
			kvT::const_iterator	elem;
			T					ret;
			bool				found;

			found = false;
			if ((elem = kv.find(key)) != kv.end())
			{
				std::istringstream	ss(elem->second);
				ss >> ret;
				found = !ss.fail();
			}
			return (std::make_pair(found, ret));
		}

		void	read(std::string filename) throw(ParseError);
		void	parse(void) throw (MissingError);

		// J'aime pas les getters moi
		std::string	admin;
		std::string	prefix;
		std::string	password;
};
