/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:18:16 by sgath             #+#    #+#             */
/*   Updated: 2021/12/04 16:01:53 by tphung           ###   ########.fr       */
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

#include <sys/time.h>

//class
#include "Connection.hpp"
#include "Connection_storage.hpp"
#include "Request.hpp"
#include "Socket.hpp"
#include "Location.hpp"
#include "ServConfig.hpp"

#include "Server.hpp"


//std::exception
class		NoValidConf : public std::exception
{
	virtual const char*	what( ) const throw( );
};

//pars
std::string	parsingConf( std::string path );

//functions
std::vector<t_server>	parse_config(int ac, char **argv);

std::map<int, std::pair<std::string, int> >
		create_listening_sockets(const std::vector<t_server>& config, std::ostream *log);

int 							puterror(std::string msg, int errno_code);
std::map<int, std::string>*		OLD_set_error_pages(const std::vector<t_server>& config);
void							set_error_pages(t_server &config, std::vector<std::string> &tokens);
void							set_default_errors(std::map<int, std::string> &ret);
std::ostream* 					open_log_file(int ac, char **av);
bool							is_file(const char *file);

#endif