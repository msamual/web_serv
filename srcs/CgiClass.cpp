#include "CgiClass.hpp"

void
CgiClass::print_char_array(char **env){
    for (int i = 0; env[i] != NULL; ++i){
        std::cout << env[i] << std::endl;
    }
    return ;
}

char **
CgiClass::make_env(){
    this->vector_env = new std::vector<std::string>;
    
    vector_env->push_back((std::string("HTTP_HOST=") + "host").data());
    vector_env->push_back((std::string("Content-Length=") + "12").data());
    vector_env->push_back(("Server_Name=" + std::string("server_name")).data());
    vector_env->push_back("VARIABLE2=sisa");
    vector_env->push_back("VARIABLE3=sosisa");

    std::string *tmp;
    env = (char **)malloc(sizeof(char *) * (vector_env->size() + 1));

    for (size_t i = 0; i < vector_env->size(); ++i){
        tmp = &(vector_env->at(i));
        env[i] = (char *)tmp->data();
    }
    env[5] = NULL;
    return env;
}

char **
CgiClass::make_argv(){
    this->vector_argv = new std::vector<std::string>;
    
    vector_argv->push_back("./cgi_bin/script.py");
    vector_argv->push_back("VARIABLE2");
    vector_argv->push_back("VARIABLE3");

    std::string *tmp;
    argv = (char **)malloc(sizeof(char *) * (vector_argv->size() + 1));

    for (size_t i = 0; i < vector_argv->size(); ++i){
        tmp = &(vector_argv->at(i));
        argv[i] = (char *)tmp->data();
    }
    argv[3] = NULL;
    return argv;
}

// CgiClass::CgiClass():
CgiClass::CgiClass(const t_server &server, Request &request):
                                    request(request),
                                    server(server),
                                    env(make_env()),
                                    argv(make_argv())
{}

CgiClass::~CgiClass(){
    free(this->env);
    free(this->argv);
    delete vector_env;
    delete vector_argv;
    return ;
}
