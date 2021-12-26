/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:01:09 by sgath             #+#    #+#             */
/*   Updated: 2021/09/11 23:11:36 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Webserv.hpp"

class Socket;
class Request;
class Connection;
class Connection_storage;

class			Server
{
	typedef std::map<int, std::pair<std::string, int> >		listen_map;

private:
	int 										_kq;
	int											_cgi_fd;
	Connection*									_cgi_conn;
	std::vector<t_server>						_config;
	listen_map									_listening_sockets;
	Connection_storage							*_connections;
	std::ostream 								*_log;

	Server();

public:

	Server(const std::vector<t_server>& config, std::ostream* log);
	Server(const Server &v);
	~Server();

	Server&		operator=(const Server &v);

	bool		start();
	void 		add_kevent_struct(struct kevent k);

	void 		add_to_read_track(int fd);

	void 		set_cgi_connection(Connection* conn);

private:
	void 		loop();
	void 		handle_events(struct kevent* events, int count);
	void 		add_listening_sockets_to_track();
	void 		add_to_write_track(int fd);
	void 		read_wrap_and_reg_cgi_response(int fd, const struct kevent& event);
};

#endif