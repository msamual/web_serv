//
// Created by Mitchel Samual on 10/27/21.
//

#ifndef WEB_SERV_SERVCONFIG_H
#define WEB_SERV_SERVCONFIG_H

# include "Webserv.hpp"

typedef struct				s_server
{
	std::vector<std::string>	names;
	std::string					host;
	std::string					root;
	std::map<int, std::string>	error_pages;
	std::vector<t_location>		locations;
	size_t						port;
}							t_server;

#endif //WEB_SERV_SERVCONFIG_H
