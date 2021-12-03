//
// Created by Mitchel Samual on 11/27/21.
//

#include "../includes/Connection_storage.hpp"

Connection_storage::Connection_storage(std::map<int, std::string>* error_pages, std::ostream* log)
	: _error_pages(error_pages), _log(log)
{}

Connection_storage::Connection_storage(const Connection_storage &other) : _connections(other._connections)
{}

Connection_storage::~Connection_storage()
{
	std::map<int, Connection*>::iterator i;
	for (i = _connections.begin(); i != _connections.end(); ++i)
		delete i->second;
}

Connection_storage&	Connection_storage::operator=(const Connection_storage &other)
{
	_connections = other._connections;
	return *this;
}

Connection&			Connection_storage::operator[](size_t i) { return *_connections[i]; }

void 				Connection_storage::add_new_connection(listen_map::iterator sock, int kq)
{
	Connection		*new_conn = new Connection(sock->first, sock->second.first, sock->second.second, _error_pages,_log);
	struct kevent	changelist;

	_connections[new_conn->getFd()] = new_conn;

	memset(&changelist, 0, sizeof(changelist));
	EV_SET(&changelist, new_conn->getFd(), EVFILT_READ, EV_ADD, 0, 0, 0);
	if (kevent(kq, &changelist, 1, NULL, 0, NULL) == -1)
		throw std::runtime_error ("add event to kqueue failed");
	*_log << "add " << changelist.ident << " fd to track" << std::endl;
}

void 				Connection_storage::close_connection(int fd)
{
	delete _connections[fd];
	_connections.erase(fd);
}