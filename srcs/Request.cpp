//
// Created by Mitchel Samual on 11/4/21.
//

#include "../includes/Request.hpp"

Request::Request()
{}

Request::Request(const std::string &str, bool is_chunked = false)
{
	std::string		req = str;

	if (is_chunked)
		parse_chunked_body(str);
	else
	{
		parse_request_string(req);
		parse_headers(req);
		parse_body(req);
	}
}

Request::Request(const Request &other)
	:	_method(other._method),
		_uri(other._uri),
		_version(other._version),
		_headers(other._headers),
		_body(other._body),
		_path(other._path)
{}

Request::~Request()
{}

Request&		Request::operator=(const Request &other)
{
	_method = other._method;
	_uri = other._uri;
	_version = other._version;
	_headers = other._headers;
	_body = other._body;
	_path = other._path;
	return *this;
}

std::ostream&	operator<<(std::ostream& stream, const Request& req)
{
	std::map<std::string, std::string>::const_iterator it = req.getHeaders().begin();

	stream << "<REQUEST>" << std::endl;
	stream << req.getMethod() << ' ' << req.getUri() << ' ' << req.getVersion() << std::endl;
	stream << "<HEADERS>" << std::endl;
	for(;it != req.getHeaders().end(); ++it)
		stream << it->first << ": " << it->second << std::endl;
	stream << "<BODY>" << std::endl;
	return stream;
}

const std::string& Request::getMethod() const {
	return _method;
}

void Request::setMethod(const std::string& method) {
	_method = method;
}

const std::string&	Request::getUri() const {
	return _uri;
}

void Request::setUri(const std::string& uri) {
	_uri = uri;
}

const std::string& Request::getVersion() const {
	return _version;
}

void Request::setVersion(const std::string& version) {
	_version = version;
}

const std::__1::map <std::string, std::string> &Request::getHeaders() const {
	return _headers;
}

const std::string&	Request::getParams() const{
	return _params;
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

void
Request::setPath(const std::string &path) { _path = path; }

void
Request::setPath(const std::string &path, const std::string &uri) {
	std::string p, u;

	if (path.back() == '/')
		p = path.substr(0, path.length() - 1);
	else
		p = path;
	if (uri.back() == '/' && uri.length() > 1)
		u = uri.substr(0, uri.length() - 1);
	else
		u = uri;
	_path = p + u;
}

const std::string&
Request::getPath() const { return _path; }

void 	Request::parse_request_string(std::string &req)
{
	std::string		first_string = req.substr(0, req.find('\r'));
	size_t 			i1	= first_string.find_first_of(' ');
	size_t 			i2	= first_string.find_last_of(' ');

	_method 	= first_string.substr(0, i1);
	_uri		= first_string.substr(i1 + 1, i2 - i1 - 1);
	_version	= first_string.substr(i2 + 1, first_string.length());

	if (_uri.find('?') != std::string::npos)
		_params = _uri.substr(_uri.find('?') + 1, std::string::npos);
	_uri = _uri.substr(0, _uri.find('?'));
//	req = req.substr(req.find('\n') + 1, req.length());
}

void 	Request::parse_headers(std::string &req)
{
	std::string 		line;
	std::istringstream	ss(req);
	std::string 		key;
	std::string 		value;
	size_t 				sep;

	std::getline(ss, line);
	while(std::getline(ss, line))
	{
		if (line == "\r")
			break ;
		else
		{
			sep = line.find(':');
			key = line.substr(0, sep);
			value = line.substr(sep + 2, line.length() - 3 - sep);
			_headers.insert(std::make_pair(key, value));
		}
	}
}

void 	Request::parse_chunked_body(const std::string &req)
{
	size_t 	i = req.find("\r\n\r\n") + 4;
	size_t 	chunk_size;
	std::string body = req.substr(i, req.size());
	std::stringstream ss(body);
	char 				buf[4096];

	while (true)
	{
		ss >> chunk_size;
		if (chunk_size == 0)
			break;
		ss.ignore('\r');
		ss.ignore();
		ss.read(buf, chunk_size);
		buf[chunk_size] = 0;
		ss.ignore('\r');
		ss.ignore();
		this->_body += buf;
	}
}

void 	Request::parse_body(std::string &req)
{

	if (_headers["Transfer-encoding"] == "chunked") {
		size_t 	i = req.find("\r\n\r\n") + 4;
		parse_chunked_body(req.substr(i, req.length()));
	}
	else if (_headers.find("Content-length") == _headers.end()
		&& _headers["Transfer-encoding"] != "chunked") {
		_body = "";
	}
	else
	{
		size_t 	i = req.find("\r\n\r\n") + 4;
		_body = req.substr(i, stoi(_headers["Content-length"]));
	}
}

