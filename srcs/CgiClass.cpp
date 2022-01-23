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
	//If the client request required authentication for external access, then the server MUST set the value of this variable
	//from the ‘auth-scheme’ token in the request Authorization HTTP header field. Otherwise the variable is set to
	//NULL

    int content_length = this->request.getBody().size();
    vector_env->push_back("CONTENT_LENGTH=" + itos(content_length));
//	The server MUST set this meta-variable if the request is accompanied by a message-body entity.
//	The CONTENT_LENGTH value must reflect the length of the message-body after the server has removed
//	any transfercodings or content-codings.

	std::string content_type;
	try {
		content_type = this->request.getHeaders().at("Content-type");
	}
	catch (std::exception &e) {
		content_type = "";
	}

	vector_env->push_back("CONTENT_TYPE=" + content_type);
    vector_env->push_back("GATEWAY_INTERFACE=CGI/1.1");
    vector_env->push_back("PATH_INFO=" + this->request.getUri());//BULLSHIT for teting purpose
    vector_env->push_back("PATH_TRANSLATED=");
    vector_env->push_back("QUERY_STRING=" + this->request.getParams());
    vector_env->push_back("REMOTE_ADDR=" + this->connection.getHost());
    vector_env->push_back("REMOTE_HOST=");//SHOULD set domain name of client if available
    //vector_env->push_back("REMOTE_IDENT=" + this->connection.getHost());//MAY be used to provide identity information
    //vector_env->push_back("REMOTE_USER=" + this->connection.getHost());//MUST set if AUTH_TYPE is set to Basic or Digest
    vector_env->push_back("REQUEST_METHOD=" + this->request.getMethod());
    vector_env->push_back("SCRIPT_NAME=" + this->request.getPath());//may NEED another format of path
    vector_env->push_back(("SERVER_NAME=" + this->connection.getHost()));

	std::string port = itos(this->connection.getPort());
	vector_env->push_back(("SERVER_PORT=" + port));

    vector_env->push_back(("SERVER_PROTOCOL=HTTP/1.1"));

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
//    const std::string   &path = this->request.getPath();
    const std::string   &params = this->request.getParams();
    
//    std::cout << "PATH = " << path << std::endl;
//    std::cout << "PARAMS = " << params << std::endl;
    // if (!is_file(path.c_str())){
        // throw std::invalid_argument("CGI script not found!");
        // http_response(403, this->connection);
    // }
    vector_argv->push_back(this->path);
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

Request & CgiClass::path_validation(Request &request)
{
	this->path = this->cgi_path;//временное решение
	this->path_info = "";

	std::string	token;
	size_t  	it = 0;
	size_t		ite = path.length();

	while(path != "")
	{
		if (is_file(path.c_str())) {
			break ;
		}
		it = path.find_last_of('/');
		this->path_info = this->path.substr(it, ite) + path_info;
		ite = it;
		this->path = this->path.substr(0, ite);
	}
	if (path == ""){
		throw std::invalid_argument("cgi script does not exist");
	}
	std::cerr << "____PATH____\n";
	std::cerr << this->path << std::endl;
	std::cerr << "____PATHINFO____\n";
	std::cerr << this->path_info << std::endl;
//    if (!is_file(request.getPath().c_str())){
//        http_response(404, connection);
//		return (-1);
//    }
	return request;
}

void	CgiClass::start() {
	path_validation(this->request);
	this->env = make_env();
	this->argv = make_argv();
	return ;
}

CgiClass::CgiClass(const t_server &server, Request &request, Connection &connection, std::string cgi_path):
                                    request(request),
                                    server(server),
                                    connection(connection),
                                    cgi_path(cgi_path)
{}

CgiClass::~CgiClass(){
//    free(this->env);
//    free(this->argv);
//    delete vector_env;
//    delete vector_argv;
    return ;
}
