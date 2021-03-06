/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 19:14:59 by sgath             #+#    #+#             */
/*   Updated: 2021/12/02 16:08:53 by msamual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const std::vector<t_server>& config, std::ostream *log)
	:	_config(config),
		_log(log)
{

	_connections = new Connection_storage(_log, _config);
	*_log << "server object was created" << std::endl;
}

Server::Server(const Server &v) :
	_config(v._config),
	_log(v._log)
{}

Server&	Server::operator=(const Server &v)
{
    if (&v != this){
        _config = v._config;
    }
    return (*this);
}

Server::~Server()
{}

bool	Server::start()
{
	_kq = kqueue();

	if (_kq == -1)
		throw std::runtime_error("kqueue() failed");
	_listening_sockets = create_listening_sockets(_config, _log);
	add_listening_sockets_to_track();
	loop();
    return true;
}

void 	Server::loop()
{
	struct kevent	events[5];
	int 			events_count;

	while(true)
	{
		*_log << "waiting..." << std::endl;
		events_count = kevent(_kq, NULL, 0, events, MAX_EVENT, NULL);
		if (events_count == -1)
			throw std::runtime_error("kevent() failed");
		handle_events(events, events_count);
	}
}

void 	Server::handle_events(struct kevent* events, int count)
{
	int						fd;
	listen_map::iterator	it;

	for (int i = 0; i < count; ++i)
	{
		fd = events[i].ident;
//		std::cerr << "event flag = " << std::hex << (int)events[i].flags << std::endl;

		*_log << "event on " << fd << " fd" << std::endl;
		if (events[i].flags & EV_ERROR) {
			throw std::runtime_error("event error");
		}
		if (fd == _cgi_fd)
		{
			read_wrap_and_reg_cgi_response(fd, events[i]);
			continue ;
		}
		it = _listening_sockets.find(fd);
		if (it != _listening_sockets.end()) {
			_connections->add_new_connection(it, _kq);
			continue;
		}
		Connection&		connection = (*_connections)[events[i].ident];
		if (events[i].flags & EV_EOF)
			_connections->close_connection(events[i].ident);
		if (events[i].flags & EVFILT_WRITE)
			connection.send_response();
		else if (events[i].flags & EVFILT_READ) {
			connection.read_request(events[i]);
            if (connection.getStatus() == COMPLETE)
                handle_requests(connection, *_log, *this);
            if (connection.getStatus() == READY) {
                add_to_write_track(fd);
            }
		}
		if (connection.getCloseConnectionFlag() & SHOULD_BE_CLOSED)
			_connections->close_connection(fd);
	}
}

void 	Server::add_listening_sockets_to_track()
{
	listen_map::iterator	i;

	for (i = _listening_sockets.begin(); i != _listening_sockets.end(); ++i)
	{
		struct kevent	changelist;

		memset(&changelist, 0, sizeof(changelist));
		EV_SET(&changelist, i->first, EVFILT_READ, EV_ADD, 0, 0, 0);
		if (kevent(_kq, &changelist, 1, NULL, 0, NULL) == -1)
			throw std::runtime_error ("add read event to kqueue failed");
		*_log << "add " << changelist.ident << " fd to track" << std::endl;
	}
}

void 	Server::add_to_read_track(int fd)
{
	struct kevent	changelist;

	memset(&changelist, 0, sizeof(changelist));
	EV_SET(&changelist, fd, EVFILT_READ, EV_ADD | EV_ONESHOT, 0, 0, 0);
	if (kevent(_kq, &changelist, 1, NULL, 0, NULL) == -1)
		throw std::runtime_error ("add read event to kqueue failed");
	this->_cgi_fd = fd;
}

void 	Server::add_to_write_track(int fd)
{
	struct kevent	changelist;

	memset(&changelist, 0, sizeof(changelist));
	EV_SET(&changelist, fd, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, 0);
	if (kevent(_kq, &changelist, 1, NULL, 0, NULL) == -1)
		throw std::runtime_error ("add write event to kqueue failed");
}

void 	Server::read_wrap_and_reg_cgi_response(int fd, const struct kevent &event)
{
	char	buf[event.data + 1];
	int		ret;
	// ret = recv(fd, buf, event.data, 0);
	ret = read(fd, buf, event.data);
	if (ret < 0)
	{
		*_log << "read from cgi failed()! fd = " << fd << std::endl;
		close(fd);
		delete _cgi_conn;
		return ;
	}
	buf[ret] = 0;
	_cgi_conn->setResponse("HTTP/1.1 200 ok\r\nHost: " + _cgi_conn->getHost() + ":"
							+ itos(_cgi_conn->getPort()) + "\r\n" + buf);
	add_to_write_track(_cgi_conn->getFd());
	_cgi_fd = -1;
	_cgi_conn = nullptr;
}

void 	Server::set_cgi_connection(Connection *conn)
{
	_cgi_conn = conn;
}