//
// Created by Mitchel Samual on 11/27/21.
//

#ifndef WEB_SERV_CONNECTION_STORAGE_H
#define WEB_SERV_CONNECTION_STORAGE_H

#include "Webserv.hpp"

class Connection;

class Connection_storage
{
	typedef std::map<int, std::pair<std::string, int> >		listen_map;

private:
	std::map<int, Connection*>	_connections;
	std::map<int, std::string>	*_error_pages;
	std::ostream 			*_log;

public:
	Connection_storage(std::map<int, std::string>* error_pages, std::ostream* log);
	Connection_storage(const Connection_storage& other);
	~Connection_storage();

	Connection_storage&		operator=(const Connection_storage& other);

	Connection&				operator[](size_t i);
	void 					add_new_connection(listen_map::iterator sock, int kq);

	void 					close_connection(int fd);
};


#endif //WEB_SERV_CONNECTION_STORAGE_H
