//
// Created by Sergey Uryashev on 21.11.2021.
//

#ifndef WEB_SERV_CONNECTION_H
#define WEB_SERV_CONNECTION_H

#define EMPTY				0
#define WAITING_HOST		1
#define INCOMPLETE			2
#define COMPLETE			3
#define READY				4
#define INVALID				5

#define DONT_CLOSE			0
#define SHOULD_BE_CLOSED	1
#define AFTER_SEND			2

#include "Webserv.hpp"

class Request;
struct Location;

class Connection
{
private:
	int 						_fd;
	std::string					_host;
	int 						_port;
	int 						_status;
	std::string					_request;
	std::string					_response;
	const t_server&             _config;
	int 						_close_connection_flag;
	std::ostream 				*_log;
	std::ofstream				*_chunked_stream;
	Request*					_cgiRequest;
	const Location*				_cgiLocation;

	Connection();
	Connection(const Connection& conn);

	Connection&		operator=(const Connection& conn);

public:
	Connection(int fd, std::string host, int port, std::ostream* log, const t_server& config);
	~Connection();

	int 				getFd() const;
	int 				getPort() const;
	const std::string&	getHost() const;
	int 				getStatus() const;
	int 				getCloseConnectionFlag() const;
	std::string& 		getRequest();
	std::string&		getResponse();
	const t_server&		getConfig();
	std::ofstream*		getChunkedStream();
//	Request&			getRequestStruct();
	Request*			getCgiRequest();
	const Location*		getCgiLocation();

	void 				setStatus(int status);
	void                setResponse(const std::string& res);
//	void 				setRequestStruct(const Request& req);
	void				setCloseConnectionFlag(int flag);
	void 				setChunkedStream(std::ofstream *chunked_stream);
	void 				setCgiRequest(Request &);
	void 				setCgiLocation(const Location &);

	void 				clear_request();
	bool 				isChunked();

	void 				read_request(const struct kevent& event);
	void 				send_response();
	std::string			get_error(int error);
};


#endif //WEB_SERV_CONNECTION_H
