//
// Created by Sergey Uryashev on 21.11.2021.
//

#include "../includes/Connection.hpp"

Connection::Connection(int fd, std::string host, int port, std::ostream* log, const t_server& config)
	: _fd(fd), _host(host), _port(port), _status(INCOMPLETE), _config(config),
	_close_connection_flag(DONT_CLOSE), _log(log)
{
	struct sockaddr	addr;
	socklen_t		len = sizeof(sockaddr);

	_fd = accept(fd, &addr, &len);
	if (_fd == -1)
		throw std::runtime_error("accept() failed");
}

Connection::~Connection()
{
	close(_fd);
	*_log << "close connection on " << _fd << " fd." << std::endl;
}

int					Connection::getFd() const { return _fd; }
int 				Connection::getPort() const { return _port; }
const std::string&	Connection::getHost() const { return _host; }
int 				Connection::getStatus() const { return _status; }
std::string&		Connection::getRequest() { return _request; }
std::string&		Connection::getResponse() { return _response; }
int 				Connection::getCloseConnectionFlag() const { return _close_connection_flag; }

void 				Connection::setStatus(int status) { _status = status; }
void                Connection::setResponse(const std::string &res) { _response = res; }
void 				Connection::clear_request() { _request = ""; }

void 				Connection::read_request(const struct kevent& event)
{
	int 	ret, size = event.data;
	char 	buf[size + 1];

	*_log << "read from " << _fd << " fd." << std::endl;
	*_log << "size = " << size << std::endl;
	ret = recv(_fd, buf, size, 0);
	*_log << "read = " << ret << std::endl;
	if (ret == -1)
	{
		std::cerr << "recv() failed from " << _fd << " fd." << std::endl;
		return;
	}
	if (ret == 0)
	{
	    _close_connection_flag = SHOULD_BE_CLOSED;
	    return ;
	}
	buf[ret] = 0;
	_request.append(buf);
	check_request();
}

void 			Connection::send_response()
{
	size_t ret;

	ret = send(_fd, _response.data(), _response.size(), 0);
	if (ret < 0)
		std::cerr << "send() failed to " << _fd << " fd." << std::endl;
//	if (ret == 0)
//		_close_connection_flag = SHOULD_BE_CLOSED;
	*_log << "send " << ret << " bytes in " << _fd << "fd." << std::endl;
	_response = "";
	_status = INCOMPLETE;
	if (_close_connection_flag & AFTER_SEND)
		_close_connection_flag = SHOULD_BE_CLOSED;
}

void 			Connection::check_request()
{
	if (_request == "\r\n")
	{
		_request = "";
		return ;
	}
	if (_status == INCOMPLETE)
	{
		std::stringstream	ss(_request);
		std::string			met, rou, ver, host, value;
		ss >> met >> rou >> ver >> host >> value;
		if  (met.find_first_not_of("ABCDEFGHIGKLMNOPQRSTUVWXYZ") != std::string::npos
            || !rou.length() || rou[0] != '/')
		{
			_response = _config.error_pages.at(400);
			_status = READY;
			_close_connection_flag = AFTER_SEND;
            return ;
		}
        if (ver != "HTTP/1.1")
        {
            _response = _config.error_pages.at(405);
            _status = READY;
            _close_connection_flag = AFTER_SEND;
            return ;
        }
        if (find_new_line(_request) > 1 && (host != "Host:" || value.length() == 0))
        {
			_response = _config.error_pages.at(400);
			_status = READY;
			_close_connection_flag = AFTER_SEND;
			return;
        }
		_status = is_complete_request(_request);
	}
}