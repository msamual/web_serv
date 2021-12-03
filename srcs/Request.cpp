//
// Created by Mitchel Samual on 11/4/21.
//

#include "Request.hpp"

Request::Request()
{}

Request::~Request()
{}

int 	Request::read_line(int fd)
{
	int 		ret = 0;
	char		buf[BUFFER_SIZE + 1];
	std::string str;

	while (true)
	{
		ret = recv(fd, buf, BUFFER_SIZE, 0);
		if (ret < 0)
			throw "recv() failed";
		if (ret < 0)
			break ;
		if (ret == 0)
			return -1;
		if (ret > 0)
		{
			buf[ret] = 0;
			str.append(buf, ret);
		}
	}
	std::cout << str << "bytes received" << std::endl;
	_request_buffer.push_back(str);
	if (str == "\r\n" || str == "\n")
		return 1;
	return 0;
}

void Request::print_request_buffer()
{
	for (size_t i = 0; i < _request_buffer.size(); ++i)
		std::cout << "- " << _request_buffer[i] << std::endl;
}

int Request::getMethod() const {
	return _method;
}

void Request::setMethod(int method) {
	_method = method;
}

const std::string&	Request::getUri() const {
	return _uri;
}

void Request::setUri(const std::string& uri) {
	_uri = uri;
}

float Request::getVersion() const {
	return _version;
}

void Request::setVersion(float version) {
	_version = version;
}

const std::__1::map <std::string, std::string> &Request::getHeaders() const {
	return _headers;
}

void Request::setHeaders(const std::__1::map <std::string, std::string> &headers) {
	_headers = headers;
}

const std::string& Request::getBody() const {
	return _body;
}

void
Request::setBody(const std::string& body) {
	_body = body;
}
