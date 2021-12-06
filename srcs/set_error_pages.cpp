//
// Created by Mitchel Samual on 12/2/21.
//

#include "Webserv.hpp"

std::map<int, std::string>*	OLD_set_error_pages(const std::vector<t_server>& config)
{
	std::map<int, std::string>	*error_pages = new std::map<int, std::string>();

	if (config.size())
		(*error_pages)[400] = "<html><head>Bad Request</head></html>\n";
	return error_pages;
}

void
set_default_errors(t_server &conf){
	conf.error_pages[400] = "<html><head>Bad Request</head></html>\n";
	return ;
}

void
set_custom_errors(t_server &conf){
	//firsts we need open a dir and parse it for some files
	//then set error page for every file in dir
	conf.error_pages[400] = "<html><head>Custom Bad Request</head></html>\n";
	return ;
}

void
set_error_pages(std::vector<t_server>& config)
{
	for (size_t i = 0; i < config.size(); ++i){
		if (config.at(i).dir_error_pages == ""){
			set_default_errors(config.at(i));
		}
		else{
			set_custom_errors(config.at(i));
		}
	}
	return ;
}
