#ifndef _CGI_H_
#define _CGI_H_

#include "Webserv.hpp"

struct Cgi{
    std::vector<std::string>    env;
    std::vector<std::string>    argv;
    Cgi(const t_server &server, Request &request);
};

#endif