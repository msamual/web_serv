//
// Created by Sergey Uryashev on 16.11.2021.
//

#include "../includes/Webserv.hpp"

int 	create_socket(const std::string& host, int port, std::ostream* log)
{
	int 					fd, ret, on = 1;
	struct sockaddr_in		addr;
	socklen_t 				addrlen = sizeof(struct sockaddr);

	*log << "creating listening socket on " << host << ":" << port <<
	std::endl;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		return puterror("can't create socket", errno);
	ret  = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if  (ret == -1)
		return puterror("setsockopt() failed", errno);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host.data());
	ret = bind(fd, (struct sockaddr*)&addr, addrlen);
	if (ret == -1)
		return puterror("bind() failed", errno);
	ret = listen(fd, 10000);
	if (ret == -1)
		return puterror("listen() failed", errno);
	return fd;
}

std::map<int, std::pair<std::string, int> >
        create_listening_sockets(const std::vector<t_server>& config, std::ostream *log)
{
	std::set<std::pair<std::string, int> >				hostports;
	std::map<int, std::pair<std::string, int> >			res;
	int 												fd;
	std::set<std::pair<std::string, int> >::iterator	i;

	for (size_t i = 0; i < config.size(); ++i)
		hostports.insert(std::pair<std::string, int>(config[i].host, config[i].port));
	for (i = hostports.begin(); i != hostports.end(); ++i)
	{
		fd = create_socket(i->first, i->second, log);
		res[fd] = *i;
	}
	return res;
};
