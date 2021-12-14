//
// Created by Mitchel Samual on 12/12/21.
//

#include "../includes/Webserv.hpp"

std::string 	get_status_msg(int n)
{
	if (n == 200)
		return "OK";
	return "OK";
}

void	make_response_get(int status, std::istream& file, Connection& conn, const Request& request)
{
	std::string		response("HTTP/1.1 " + std::to_string(status) + " " + get_status_msg(status) + "\r\n");
	std::string 	content;
	std::string 	content_type = "text/html";

	std::getline(file, content, (char)EOF);
	if (request.getHeaders().find("Accept") != request.getHeaders().end())
		content_type = request.getHeaders().at("Accept").substr(0, request.getHeaders().at("Accept").find(','));

	response += "Host: " + conn.getHost() + ":" + std::to_string(conn.getPort()) + "\r\n";
	response += "Content-type: " + content_type + "\r\n";
	response += "Content-length: " + std::to_string(content.length() + 1) + "\r\n\r\n";
	response += content + "\r\n\r\n";
//	response += (char)EOF;

	conn.setResponse(response);
}