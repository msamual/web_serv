//
// Created by Mitchel Samual on 12/2/21.
//

#include "Webserv.hpp"

void
set_default_errors(std::map<int, std::string> &ret){
	ret[400] = "<html><head>Bad Request</head></html>";
	ret[401] = "<html><head>Unauthorized</head></html>";
	ret[403] = "<html><head>Forbidden</head></html>";
	ret[404] = "<html><head>Not found</head></html>";
    ret[405] = "<html><head>Not allowed</head></html>";
	ret[500] = "<html><head>Internal server error</head></html>";
	ret[501] = "<html><head>Not Implemented</head></html>";
	ret[502] = "<html><head>Bad Gateway</head></html>";
	ret[503] = "<html><head>Service Unavaiable</head></html>";
	ret[521] = "<html><head>Web server is down</head></html>";
	return ;
}

void
set_error_pages(t_server &config, std::vector<std::string> &tokens)
{
	int	error;

	if (tokens.size() != 3){
		throw (std::invalid_argument("Error pages are invalid"));
	}
	else if (!is_file(tokens.at(2).c_str())){
		throw (std::invalid_argument("Error pages are not a files"));
	}
	error = atoi(tokens.at(1).c_str());

	std::ifstream			infile(tokens.at(2));
	std::stringstream 		buffer;
	buffer << infile.rdbuf();
	config.error_pages[error] = buffer.str();
	infile.close();
	return ;
}
