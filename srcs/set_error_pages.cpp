//
// Created by Mitchel Samual on 12/2/21.
//

#include "Webserv.hpp"

std::map<int, std::string>*	set_error_pages(const std::vector<t_server>& config)
{
	std::map<int, std::string>	*error_pages = new std::map<int, std::string>();

	if (config.size())
		(*error_pages)[400] = "<html><head>Bad Request</head></html>\n";
	return error_pages;
}
