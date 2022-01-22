//
// Created by Mitchel Samual on 1/15/22.
//

#include "../includes/Webserv.hpp"

typedef std::map<std::string, std::string>		map;

std::ofstream	*write_new_file(const std::string& file, const std::string& content, std::ostream& out)
{
	std::ofstream	*file_stream = new std::ofstream();

	file_stream->open(file, std::ofstream::trunc);
	if (file_stream->is_open())
	{
		file_stream->write(content.data(), content.size());
		return file_stream;
	}
	else
	{
		out << "Cant open file: " << file << std::endl;
		return NULL;
	}
}


void 	handle_POST(std::ostream& out, Request& request, const Location& location, Connection& conn)
{
	std::string 	res_name = location.upload_dir + get_res_path(location.location, request.getUri());
	int 			status_code;
	std::ofstream 	*file_stream;
	std::string 	body = request.getBody();

	if (conn.isChunked()){
		//add request body to connection chunked_stream
		file_stream = conn.getChunkedStream();
		if (body.empty()){
			file_stream->close();
			delete file_stream;
			conn.setChunkedStream(NULL);
		}
		else {
			file_stream->write(body.data(), body.size());
		}
		return ;
	}
//	map::const_iterator content_length = request.getHeaders().find("Content-Length");

//	if (cotent_length == request.getHeaders().end())
//		return http_response(411, conn);
	if (is_file(res_name.data()))
	{
		file_stream = write_new_file(res_name, request.getBody(), out);
		if (file_stream != NULL)
			status_code = 200;
		else {
			http_response(status_code = 500, conn, request.getMethod());
			return;
		}
	}
	else
	{
		file_stream = write_new_file(res_name, request.getBody(), out);
		if (file_stream != NULL)
			status_code = 201;
		else {
			http_response(status_code = 500, conn, request.getMethod());
			return;
		}
	}
	if (request.isChunked()) {
		conn.setChunkedStream(file_stream);
	}
	else {
		file_stream->close();
		delete file_stream;
	}
	make_response_put(status_code, conn);
}