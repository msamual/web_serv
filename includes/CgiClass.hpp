#ifndef _CGI_CLASS_H_
#define _CGI_CLASS_H_

# include "Webserv.hpp"

struct CgiClass{
    Request         &request;
    const t_server  &server;
    Connection      &connection;
    std::string		path;
    std::string 	path_info;
    std::string 	cgi_path;
    char     		**env;
    char     		**argv;
    std::vector<std::string>    *vector_env;
    std::vector<std::string>    *vector_argv;
    char**    		make_env();
    char**    		make_argv();
    void            print_char_array(char **array);
    void            tokenize(const std::string &params);
    Request 		&path_validation(Request &request);
    void 			start();
	CgiClass(const t_server &server, Request &request, Connection &connection, std::string cgi_path);
	~CgiClass();
};

#endif
