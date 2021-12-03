//
// Created by Sergey Uryashev on 12.11.2021.
//

#include "Webserv.hpp"

std::vector<t_server>	parse_config(int argc, char **argv)
{
	if(argc < 2 || !argv)
		throw (std::runtime_error("Error: no config path\n"
								  " ...usage \"webserv PATH_TO_CONFIG\""));
	std::vector<t_server>	result;
	t_server				simple_conf;

	simple_conf.port = 8080;
	simple_conf.host = "127.0.0.1";
	result.push_back(simple_conf);
	simple_conf.host = "127.0.0.1";
	simple_conf.port = 8081;
	result.push_back(simple_conf);
	result.push_back(simple_conf);
	return result;
}