//
// Created by Mitchel Samual on 10/27/21.
//

#ifndef WEB_SERV_SOCKET_H
#define WEB_SERV_SOCKET_H

#include "Webserv.hpp"

class Socket
{
private:
	int			_fd;
	int			_port;
	std::string _host;

public:
	Socket(int port = 8080, const std::string& host = "127.0.0.1");
	Socket(int fd, int port = 8080, const std::string& host = "127.0.0.1");
	~Socket();

	Socket*		new_connection();
	
	int getFd() const;
	int getPort() const;

	void setFd(int fd);
	void setPort(int port);
};


#endif //WEB_SERV_SOCKET_H
