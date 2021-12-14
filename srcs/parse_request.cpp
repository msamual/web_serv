//
// Created by Mitchel Samual on 12/11/21.
//

#include "../includes/Webserv.hpp"

const Request& 	parse_request(Connection& connection)
{
	Request*	request = new Request(connection.getRequest());

	return *request;
}