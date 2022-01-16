//
// Created by Mitchel Samual on 1/15/22.
//

#include "../includes/Webserv.hpp"

typedef std::map<std::string, std::string>		map;

void 	handle_POST(std::ostream& out, Request& request, const Location& location, Connection& conn)
{
	map::const_iterator cotent_length = request.getHeaders().find("Content-Length");

	if (cotent_length == request.getHeaders().end())
		return http_response(411, conn);
}