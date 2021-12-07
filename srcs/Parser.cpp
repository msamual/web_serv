#include "Webserv.hpp"

bool
is_file(const char *file)
{
    struct stat path_stat;

    stat(file, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

bool
not_space(char i)
{
    return !isspace(i);
}

std::vector<std::string>
*tokenize(std::string line)
{
    std::string             token;
    std::string::iterator   it;
    std::string::iterator   ite;
    std::vector<std::string> *ret = new std::vector<std::string>;

    ite = line.begin();
    while (ite != line.end()){
        it = find_if(ite, line.end(), not_space);
        ite = find_if(it, line.end(), isspace);
        token.resize(ite - it);
        std::copy(it, ite, token.begin());
        ret->push_back(token);
    }
    return ret;
}

void
check_address(std::string& input, t_server &config)
{
    size_t 		i;
    std::string port;

    if ((i = input.find(':', 0)) == std::string::npos){
        if (input != "localhost" && (i = input.find('.', 0)) == std::string::npos){
            config.host = "0.0.0.0";
            port = input;
        }
        else {
            port = "8080";
            config.host = input;
        }
    }
    else{
        config.host.resize(i);
        std::copy(input.begin(), input.begin() + i, config.host.begin());
        port.resize(input.size() - i - 1);
        std::copy(input.begin() + i + 1, input.end(), port.begin());
    }
    if (config.host == "localhost")
        config.host = "127.0.0.1";
    if (port.find_last_not_of("0123456789") != std::string::npos)
        throw std::invalid_argument("Bad port!");
    config.port = std::atoi(port.c_str());
    return ;
}

int
make_config(std::vector<std::string> &tokens, std::vector<t_server> &ret)
{
    if (tokens.at(0) == "server"){
        ret.push_back(t_server());
        set_default_errors(ret.back().error_pages);
    }
    else if (tokens.at(0) == "error_page"){
        set_error_pages(ret.back(), tokens);
    }
    else if (tokens.at(0) == "listen"){
        check_address(tokens.at(1), ret.back());
        if (tokens.size() == 3 && tokens.at(2) == "default"){
            ret.back().default_server = true;
        }
    }
    else if (tokens.at(0) == "server_names"){
        for (size_t i = 1; i < tokens.size(); ++i){
            ret.back().names.push_back(tokens.at(i));
        }
    }
    else if (tokens.at(0) == "body_size"){
        ret.back().body_size = std::atoi(tokens.at(1).c_str());
    }
    else if (tokens.at(0) == "location"){
        ret.back().locations.push_back(Location());
        if (tokens.size() > 1){
            ret.back().locations.back().location = tokens.at(1);
        }
        return 1;
    }
    return 0;
}

bool
make_location(std::vector<std::string> &tokens, Location &ret)
{

    if (tokens.at(0) == "}")
        return false;
    else if (tokens.at(0) == "accepted_methods"){
        for (size_t i = 1; i < tokens.size(); ++i){
            ret.accepted_methods += tokens.at(i) + " ";
        }
    }
    else if (tokens.at(0) == "redirection"){
        ret.redirection = tokens.at(1);
    }
    else if (tokens.at(0) == "root"){
        ret.root = tokens.at(1);
    }
    else if (tokens.at(0) == "dir_listing"){
        if (tokens.at(1) == "true"){
            ret.dir_listing = true;
        }
    }
    else if (tokens.at(0) == "default_file"){
        ret.default_file = tokens.at(1);
    }
    else if (tokens.at(0) == "cgi"){
        ret.cgi = tokens.at(1);
    }
    else if (tokens.at(0) == "upload_dir"){
        ret.upload_dir = tokens.at(1);
    }
    return true;
}

std::vector<t_server>
pratt_parser(std::string &file)
{
    std::vector<t_server>   ret;// = new std::vector<t_server>;
    std::string             line;
    std::vector<std::string> *tokens;
    bool                    location_flag = false;
    std::ifstream           infile(file);

    while (std::getline(infile, line)){
        tokens = tokenize(line);
        if (tokens->size() != 0){
            if (location_flag){
                location_flag = make_location(*tokens, ret.back().locations.back());
            }
            else{
                location_flag = make_config(*tokens, ret);
            }
        }
        // print config content from tokens
        // for (size_t i = 0; i < tokens->size(); ++i){
        //     std::cout << tokens->at(i) << ' ';
        // }
        // std::cout << std::endl;
        delete tokens;
    }
    infile.close();
    return ret;
}

std::vector<t_server>
parse_config(int ac, char **argv)
{
    std::vector<std::string>    tokens;
    std::vector<t_server>       ret;
    std::string                 tmp;
    int                         i;
    std::string                 arg1 = argv[1];

    std::cout << arg1 << std::endl;
    for (i = 1; i <= ac; ++i){
        if (i == ac){
            tmp = "conf_files/.def_config.ft";
        }
        else if (is_file(argv[i])){
            tmp = argv[i];
            if (tmp.compare(tmp.size() - 3, 3, ".ft") == 0){
                break ;
            }
        }
    }
    ret = pratt_parser(tmp);
    std::cout << ret[0].host << std::endl;
    // if (ac == 1){                       //make default config
    //     ret = pratt_parser("conf/files");
    // }
    // if (ac == 2 || ac == 3){                  //parse config
    //     if (!is_file(argv[1])){
    //         throw std::invalid_argument("Bad config file!");
    //     }
    //     ret = pratt_parser(argv[1]);
    // }
    // else{                               //just error
    //     throw std::invalid_argument("Wrong arguments!");
    // }
    return ret;
}
