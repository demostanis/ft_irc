/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:30:13 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/08 15:40:49 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define DEFINE_EXCEPTION(name)             \
	class	name ## Error                  \
	{                                      \
	private:                               \
		std::string	message;               \
	public:                                \
		name ## Error(std::string message) \
			: message(message)             \
		{                                  \
		}                                  \
		                                   \
		const char	*what() const          \
		{                                  \
			return (message.c_str());      \
		}                                  \
	};
