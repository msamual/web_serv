//
// Created by Mitchel Samual on 1/15/22.
//

#include "../includes/Webserv.hpp"

typedef std::map<std::string, std::string>		map;

bool 	write_in_file(const std::string& file, const std::string& content, std::ostream& out)
{
	std::ofstream file_stream;

	file_stream.open(file, std::ofstream::trunc);
	if (file_stream.is_open())
	{
		file_stream.write(content.data(), content.size());
		return true;
	}
	else
	{
		out << "Cant open file: " << file << std::endl;
		return false;
	}
}



void 	handle_POST(std::ostream& out, Request& request, const Location& location, Connection& conn)
{
//	map::const_iterator content_length = request.getHeaders().find("Content-Length");
	std::string 	res_name = location.upload_dir + get_res_path(location.location, request.getUri());
	int 			status_code;

//	if (cotent_length == request.getHeaders().end())
//		return http_response(411, conn);
	if (is_file(res_name.data()))
	{
		if (write_in_file(res_name, request.getBody(), out) == true)
			status_code = 200;
		else
			http_response(status_code = 500, conn, request.getMethod());
	}
	else
	{
		if (write_in_file(res_name, request.getBody(), out) == true)
			status_code = 201;
		else
			http_response(status_code = 500, conn, request.getMethod());
	}
	make_response_put(status_code, conn);
}