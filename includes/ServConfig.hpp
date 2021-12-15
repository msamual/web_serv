#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

struct Location{
    std::string location;
    std::string accepted_methods;
    std::string redirection;
    std::string root;

    bool        auto_index;
    std::string default_file;

    std::string cgi;
    std::string upload_dir;
};

struct t_server{
    std::string                 host;
    size_t                      port;
    bool                        default_server;
    std::vector<std::string>    names;
    std::map<int, std::string>  error_pages;
    int                         body_size;
    std::vector<Location>       locations;
    bool                        cgi;
};

#endif
