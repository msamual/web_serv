//
// Created by Mitchel Samual on 11/4/21.
//

#ifndef WEB_SERV_REQUEST_H
# define WEB_SERV_REQUEST_H

#include "Webserv.hpp"

# define GET 1

class Request
{
private:

	int 								_fd;
	int 								_method;
	std::string							_uri;
	float 								_version;
	std::map<std::string, std::string>	_headers;
	std::string 						_body;
	std::vector<std::string>			_request_buffer;

public:
	Request();
	Request(const Request& other);
	~Request();

	Request&	operator=(const Request& other);

	int 	read_line(int fd);
	void 	print_request_buffer();

	int getMethod() const;
	float getVersion() const;
	const std::string &getUri() const;
	const std::map<std::string, std::string> &getHeaders() const;
	const std::string &getBody() const;

	void setMethod(int method);
	void setVersion(float version);
	void setUri(const std::string &uri);
	void setHeaders(const std::map<std::string, std::string> &headers);
	void setBody(const std::string &body);


};


#endif //WEB_SERV_REQUEST_H
