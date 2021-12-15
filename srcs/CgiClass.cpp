#include "Webserv.hpp"



Cgi::Cgi(const t_server &server, Request &request)
{
    env.push_back(std::string("HTTP_HOST=") + server.host);
    env.push_back(std::string("Content-Length=") + "12");
    env.push_back(("Server_Name="+server.names[0]).data());
    env.push_back("VARIABLE2=sisa");
    env.push_back("VARIABLE3=sosisa");
    env.push_back(NULL);

    argv.push_back(server.locations.back().default_file);
    argv.push_back(request.getPath() + "\0");
    argv.push_back("VARIABLE2");
    argv.push_back("VARIABLE3");
    argv.push_back(NULL);
}
