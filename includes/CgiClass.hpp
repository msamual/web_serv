#ifndef _CGI_CLASS_H_
#define _CGI_CLASS_H_

# include "Webserv.hpp"

struct CgiClass{
    Request         &request;
    const t_server  &server;
    Connection      &connection;
    char      **env;
    char      **argv;
    std::vector<std::string>    *vector_env;
    std::vector<std::string>    *vector_argv;
    char**    make_env();
    char**    make_argv();
    void            print_char_array(char **array);
    void            tokenize(const std::string &params);
    CgiClass(const t_server &server, Request &request, Connection &connection);
    // CgiClass();
    ~CgiClass();
};

#endif
