//
// Created by Mitchel Samual on 12/7/21.
//

#include "../includes/Webserv.hpp"

const Location&		find_location(const std::string& uri, const std::vector<Location>& locations)
{
	size_t 		max_match = 0;
	size_t 		max_index = 0;

	for (size_t i = 0; i < locations.size(); ++i)
	{
		size_t count = 0;
		while (uri[count] == locations[i].location[count])
			++count;
		if (count > max_match)
		{
			max_match = count;
			max_index = i;
		}
	}
	return locations[max_index];
}

bool 	is_directory(std::string file_path)
{
	struct stat stat;
	int 		ret;

	ret = lstat(file_path.data(), &stat);
	if (ret == -1)
		return false;
	if (stat.st_mode & S_IFDIR)
		return true;
	return false;
}

void 	handle_file(std::ostream& out, Request& request, const Location& location, Connection& conn)
{
	out << "fd " << conn.getFd() << "." << std::endl;
	out << "location [" << location.location << "]" << std::endl;
	out << "path [" << request.getPath() << "]" << std::endl;
	out << "URI [" << request.getUri() << "]" << std::endl;

	std::string			index_name = request.getPath();
	if (is_file(index_name.data()))
	{
		std::ifstream 	file(index_name);
		if (file.good())
		{
			request.setPath(request.getPath(), "index.html");
			make_response_get(200, file, conn, request);
		}
	}
}

void 	handle_dir(std::ostream& out, Request& request, const Location& location, Connection& conn)
{
	out << "fd " << conn.getFd() << "." << std::endl;
	out << "location [" << location.location << "]" << std::endl;
	out << "path [" << request.getPath() << "]" << std::endl;
	out << "URI [" << request.getUri() << "]" << std::endl;

	std::string			index_name = request.getPath() + "/index.html";
	if (is_file(index_name.data()))
	{
		request.setPath(request.getPath(), "/index.html");
		handle_file(out, request, location, conn);
	}
	else if (location.auto_index){
		dir_listing_response(request.getPath(), request.getUri(), conn);
	}
	else{
		http_response(404, conn);
	}
}

void	handle_GET(std::ostream& out, Request& request, const Location& location, Connection& conn)
{
	if (is_directory(request.getPath()))
		handle_dir(out, request, location, conn);
	else
		handle_file( out, request, location, conn);

}

void    handle_requests(Connection& conn, std::ostream& out)
{
	Request				request(conn.getRequest());
	const Location		&location = find_location(request.getUri(), conn.getConfig().locations);

	request.setPath(location.root, request.getUri());
	if (request.getMethod() == "GET" && location.accepted_methods.find("GET") != std::string::npos)
		handle_GET(out, request, location, conn);
	conn.clear_request();
    conn.setStatus(READY);
}