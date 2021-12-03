/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 14:31:01 by sgath             #+#    #+#             */
/*   Updated: 2021/09/12 16:03:36 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"


Parser::Parser( )
{}

Parser::Parser( std::string path) :		confPath( path )
{
	std::ofstream	file(confPath, std::ios_base::in);
	if (!file.is_open() || file.bad())
		throw Parser::CantOpenConf();
}

Parser::Parser( const Parser &e ) :		confPath(e.confPath)
{}

Parser				Parser::operator=( const Parser &v)
{
	if (&v != this){
		confPath = v.confPath;
	}
	return (*this);
}

Parser::~Parser( )
{}

std::string	Parser::getConfPath( )
{
	return confPath;
}

const char*			Parser::CantOpenConf::what( ) const throw()
{
	return "file cant be open!";
}