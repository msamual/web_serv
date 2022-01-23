//
// Created by Mitchel Samual on 12/9/21.
//

#include "../includes/Webserv.hpp"

bool 	is_address(const std::string& str)
{
	if (str.find("http://") == std::string::npos && str[0] != '/')
		return false;
	return true;
}

int     find_new_line(const std::string& str)
{
    int res = 0;

    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == '\r' && str[i + 1] == '\n')
            ++res;
    }
    return res;
}

int 	is_content_length(const std::string& str)
{
	std::stringstream	ss(str);
	std::string 		cont;
	int 				len = 0;

	ss >> cont >> len;
	if (cont == "Content-length:")
		return len;
	return 0;
}

int 	is_complete_request(const std::string& request)
{
	std::stringstream	ss(request);
	std::string			str;
	bool 				body = false;

	while (std::getline(ss, str))
	{
		if (is_content_length(str))
			body = true;
		if (str == "\r")
		{
			if (body == true)
				body = false;
			else if (request.substr(request.length() - 4, request.length()) == "\r\n\r\n")
				return COMPLETE;
		}
	}
	return INCOMPLETE;
}

std::string		itos(int num)
{
	std::stringstream	ss;

	ss << num;
	return ss.str();
}

bool 			check_request(Connection& conn)
{
	std::string str = conn.getRequest();

	if (str == "\r\n")
	{
		str = "";
		return false;
	}
	std::stringstream	ss(str);
	std::string			met, rou, ver, host, value;
	ss >> met >> rou >> ver >> host >> value;
	if  (met.find_first_not_of("ABCDEFGHIGKLMNOPQRSTUVWXYZ") != std::string::npos
	|| !is_address(rou))
	{
		http_response(400, conn);
		return false;
	}
	if (ver != "HTTP/1.1")
	{
		http_response(405, conn);
		return false;
	}
	if (find_new_line(str) > 1 && (host != "Host:" || value.length() == 0))
	{
		http_response(400, conn);
		return false;
	}
	return true;
}

std::string 	get_res_path(const std::string& location, const std::string& uri)
{
	int i = 0;

	while (location[i] && location[i] == uri[i])
		++i;
	return uri.substr(i, uri.length());
}
