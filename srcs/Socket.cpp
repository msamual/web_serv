#include "Socket.hpp"

Socket::Socket(int port, const std::string& host) :	_port(port),
													_host(host)
{
	int					ret, on = 1;
	struct sockaddr_in	addr;
	in_addr_t 		ip;

	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)
		throw "Socket() failed";
	ret = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if (ret < 0)
		throw "setsockopt() failed";
	ret = fcntl(_fd, F_SETFL, O_NONBLOCK);
	if (ret < 0)
		throw "fcntl() failed";
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	ip = inet_addr(_host.data());
	memcpy(&addr.sin_addr, &ip, sizeof(in_addr));
	addr.sin_port = htons(_port);
	ret = bind(_fd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
	if (ret < 0)
		throw "bind() failed";
	ret = listen(_fd, CONN_NUMBER);
	if (ret < 0)
		throw "listen() failed";
}

Socket::Socket(int fd, int port, const std::string& host) :	_fd(fd),
															_port(port),
															_host(host)
{}

Socket::~Socket()
{
	close(_fd);
}

Socket*		Socket::new_connection()
{
	int new_fd = accept(_fd, NULL, NULL);
	if (new_fd < 0 && errno != EWOULDBLOCK)
			throw "accept() failed";
	if (new_fd > -1)
	{
		std::cout << "New incoming connection on " << new_fd << "fd" << std::endl;
		return new Socket(new_fd, _port, _host);
	}
	return nullptr;
}

int Socket::getFd() const {
	return _fd;
}

void Socket::setFd(int fd) {
	_fd = fd;
}

int Socket::getPort() const {
	return _port;
}

void Socket::setPort(int port) {
	_port = port;
}
