//
// Created by Mitchel Samual on 12/9/21.
//

#include "../includes/Webserv.hpp"

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
			else
				return COMPLETE;
		}
	}
	return INCOMPLETE;
}

std::string
itos(int num){
	std::stringstream	ss;

	ss << num;
	return ss.str();
}
