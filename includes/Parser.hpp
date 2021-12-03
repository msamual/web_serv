/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:27:47 by sgath             #+#    #+#             */
/*   Updated: 2021/09/12 16:01:26 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Webserv.hpp"

class Parser
{
private:
	std::string		confPath;

public:
	Parser( );
	Parser( std::string path );
	Parser( const Parser &v );
	Parser			operator=( const Parser &v );
	~Parser();

	std::string		getConfPath();
	
	//std::exception
	class			CantOpenConf : public std::exception
	{
		virtual const char*	what( ) const throw( );
	};

	class			NoValidConf : public std::exception
	{
		virtual const char*	what( ) const throw( );
	};

};



#endif
