//
// Created by Mitchel Samual on 10/27/21.
//

#ifndef WEB_SERV_LOCATION_H
#define WEB_SERV_LOCATION_H

# include "Webserv.hpp"

typedef struct				s_location
{
	bool 						_autoindex;
	bool 						_uploading_enable;
	std::string					_name;
	std::string 				_root;
	std::vector<std::string>	_methods;
	std::vector<std::string>	_index;
	std::vector<std::string>	_cgi_extensions;
	std::string 				_cgi_path;
	std::string 				_uploading_path;
	size_t						_client_max_count;
}							t_location;


#endif //WEB_SERV_LOCATION_H
