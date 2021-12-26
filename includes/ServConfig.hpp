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
    bool        is_default;
    Location(): accepted_methods("GET POST DELETE"),
                root("./test_site"),
                auto_index(true),
                default_file("index.html"),
                cgi(""),
                is_default(true)
    {};
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
    t_server(){
        host = "localhost";
        port = 8080;
        default_server = false;
        body_size = 10000000;
    };
};

#endif
