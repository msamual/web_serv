//
// Created by Mitchel Samual on 11/4/21.
//

#ifndef WEB_SERV_REQUEST_H
# define WEB_SERV_REQUEST_H

#include "../includes/Webserv.hpp"

class Request
{
private:

	std::string 						_method;
	std::string							_uri;
	std::string 						_version;
	std::map<std::string, std::string>	_headers;
	std::string 						_body;
	std::string							_path;
	std::string 						_params;

public:
	Request();
	Request(const std::string& str, bool is_chunked);
	Request(const Request& other);
	~Request();

	Request&	operator=(const Request& other);


	const std::string&							getMethod() const;
	const std::string&							getVersion() const;
	const std::string&							getUri() const;
	const std::map<std::string, std::string>&	getHeaders() const;
	const std::string&							getBody() const;
	const std::string&							getPath() const;
	const std::string&							getParams() const;

	void 										setMethod(const std::string& method);
	void 										setVersion(const std::string& version);
	void 										setUri(const std::string &uri);
	void 										setHeaders(const std::map<std::string, std::string> &headers);
	void 										setBody(const std::string &body);
	void 										setPath(const std::string &path);
	void 										setPath(const std::string &root, const std::string &uri);

	bool 										isChunked();

	void 										parse_request_string(std::string& req);
	void 										parse_headers(std::string& req);
	void 										parse_body(std::string& req);
	void 										parse_chunked_body(const std::string& req);
};

std::ostream&									operator<<(std::ostream& stream, const Request& req);


#endif //WEB_SERV_REQUEST_H
