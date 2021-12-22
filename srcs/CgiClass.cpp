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
    
    vector_env->push_back("AUTH_TYPE=");
    vector_env->push_back("CONTENT_LENGTH=");
    vector_env->push_back("CONTENT_TYPE=");
    vector_env->push_back("GATEWAY_INTERFACE=CGI/1.1");
    vector_env->push_back("PATH_INFO=");
    vector_env->push_back("PATH_TRANSLATED=");
    vector_env->push_back("QUERY_STRING=" + this->request.getParams());
    vector_env->push_back("REMOTE_ADDR=" + this->connection.getHost());
    vector_env->push_back("REMOTE_HOST=");//SHOULD set domain name of client if available
    //vector_env->push_back("REMOTE_IDENT=" + this->connection.getHost());//MAY be used to provide identity information
    //vector_env->push_back("REMOTE_USER=" + this->connection.getHost());//MUST set if AUTH_TYPE is set to Basic or Digest
    vector_env->push_back("REQUEST_METHOD=" + this->request.getMethod());
    vector_env->push_back((std::string("HTTP_HOST=") + "host").data());
    vector_env->push_back(("Server_Name=" + std::string("server_name")).data());

    std::string *tmp;
    env = (char **)malloc(sizeof(char *) * (vector_env->size() + 1));

    for (size_t i = 0; i < vector_env->size(); ++i){
        tmp = &(vector_env->at(i));
        env[i] = (char *)tmp->data();
    }
    env[vector_env->size()] = NULL;
    return env;
}

void
CgiClass::tokenize(const std::string &params)
{
    std::string             token;
    size_t  it = 0;
    size_t  ite = 0;

    while (ite < params.npos){
        ite = params.find('&', it);
        token = params.substr(it, ite - it);
        this->vector_argv->push_back(token);
        it = ite + 1;
    }
    return ;
}

char **
CgiClass::make_argv(){
    this->vector_argv = new std::vector<std::string>;
    const std::string   &path = this->request.getPath();
    const std::string   &params = this->request.getParams();
    
    std::cout << "PATH = " << path << std::endl;
    std::cout << "PARAMS = " << params << std::endl;
    if (!is_file(path.c_str())){
        throw std::invalid_argument("CGI script not found!");
    }
    vector_argv->push_back(path);
    if (params != ""){
        this->tokenize(params);
    }

    std::string *tmp;
    argv = (char **)malloc(sizeof(char *) * (vector_argv->size() + 1));

    for (size_t i = 0; i < vector_argv->size(); ++i){
        tmp = &(vector_argv->at(i));
        argv[i] = (char *)tmp->data();
    }
    argv[vector_argv->size()] = NULL;
    return argv;
}

// CgiClass::CgiClass():
CgiClass::CgiClass(const t_server &server, Request &request, Connection &connection):
                                    request(request),
                                    server(server),
                                    connection(connection),
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
