//
// Created by Mitchel Samual on 11/27/21.
//

#include "../includes/Connection_storage.hpp"

Connection_storage::Connection_storage(std::ostream* log, const std::vector<t_server>& config)
	: _log(log), _config(config)
{}

Connection_storage::Connection_storage(const Connection_storage &other)
: _connections(other._connections), _config(other._config)
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
    const t_server&	config = find_config(sock, _config);
	Connection		*new_conn = new Connection(sock->first, sock->second.first, sock->second.second, _log, config);
	struct kevent	changelist;

	_connections[new_conn->getFd()] = new_conn;

	memset(&changelist, 0, sizeof(changelist));
	EV_SET(&changelist, new_conn->getFd(), EVFILT_READ, EV_ADD, 0, 0, 0);
	if (kevent(kq, &changelist, 1, NULL, 0, NULL) == -1)
		throw std::runtime_error ("add event to kqueue failed");
	*_log << "add " << changelist.ident << " fd to track" << std::endl;
}

const t_server&		Connection_storage::find_config(listen_map::iterator sock, const std::vector<t_server>& conf)
{
    std::string host = sock->second.first;
    size_t 		port = sock->second.second;

    for (size_t i = 0; i < conf.size(); ++i)
    {
        if (conf[i].host == host && conf[i].port == port)
            return conf[i];
    }
    return conf[0];
}

void 				Connection_storage::close_connection(int fd)
{
//	std::cout << "Произошел разрыв соединения Request=" + _connections[fd]->getRequest() << std::endl;
//	std::cout << "Response =\n" << _connections[fd]->getResponse() << std::endl;
//	std::cout << "Status = " << _connections[fd]->getStatus() << std::endl;
//	std::cout << "Close connection flag = " << _connections[fd]->getCloseConnectionFlag() << std::endl;
	delete _connections[fd];
	_connections.erase(fd);
}