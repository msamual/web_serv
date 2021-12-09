#include <Webserv.hpp>

static const int ENV_LEN = 3;

void
print_env(const char **env){
    for (int i = 0; env[i] != NULL; ++i){
        std::cout << env[i] << std::endl;
    }
    return ;
}

int
cgi(t_server &server)
{
    static const char *env[ENV_LEN] = {
        (std::string("HTTP_HOST=") + server.host).data(),
        server.names[0].data(),
        NULL,
    };
    static const char *argv[4] = {
        "./a.out",
        "first argument",
        "second argument",
        NULL
    };


    return 0;
}
