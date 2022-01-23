/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:18:16 by sgath             #+#    #+#             */
/*   Updated: 2021/12/15 16:33:22 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

# define CONN_NUMBER 10000
# define BUFFER_SIZE 16
# define MAX_EVENT	128

// Colors
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"

# define RESET "\033[34m"


#include <iostream>
#include <memory>
#include <unistd.h>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <exception>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/stat.h>
#include <dirent.h>

#include <sys/time.h>

//class
#include "Request.hpp"
#include "ServConfig.hpp"
#include "Connection.hpp"
#include "Connection_storage.hpp"
#include "Request.hpp"
#include "Socket.hpp"
#include "Server.hpp"

class Server;

//functions
std::vector<t_server>			parse_config(int ac, char **argv);

std::map<int, std::pair<std::string, int> >
								create_listening_sockets(const std::vector<t_server>& config, std::ostream *log);

int 							puterror(std::string msg, int errno_code);
void							set_error_pages(t_server &config, std::vector<std::string> &tokens);
void							set_default_errors(std::map<int, std::string> &ret);
std::ostream* 					open_log_file(int ac, char **av);
bool							is_file(const char *file);
int								cgi(const t_server &server, Request &request, Connection &connection, const Location &location);
void                            handle_requests(Connection& conn, std::ostream& out, Server& server);
int								find_new_line(const std::string& str);
int							 	is_complete_request(const std::string& request);
const Request&				 	parse_request(Connection& connection);
void							make_response_get(int status, std::istream& file, Connection& conn, const Request& request);
void 							http_response(int status, Connection &connection);
void 							http_response(int status, Connection &connection, std::string method);
void							dir_listing_response(const std::string &path, const std::string& root, Connection &connection);
std::string						status_to_text(int status);
std::string						itos(int num);
bool 							is_address(const std::string& str);
void 							handle_POST(std::ostream& out, Request& request, const Location& location, Connection& conn);
bool							check_request(Connection& conn);
std::string					 	get_res_path(const std::string& location, const std::string& uri);
bool 							is_file(const char *file);
void						 	make_response_put(int status, Connection& conn);


#endif