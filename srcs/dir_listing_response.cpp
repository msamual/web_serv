#include "../includes/Webserv.hpp"

std::string html_from_dir(const std::string &path, const std::string &root, std::string host, std::string port)
{
	DIR				*dir;
	struct dirent	*example = NULL;
    std::string     ret;
    std::string     tmp_root;

    ret = "<html><head><title>" + path + "/" + "</title></head><body>";

	dir = opendir(path.c_str());
    errno = 0;
	if (!dir){
        return "";
    }
	for (example = readdir(dir); example != NULL; example = readdir(dir)){
		if (!example)
			break ;
        if (std::string(example->d_name) == "."){
            ret += "<p><a href=\"http://" + host + ":" + port + root + "\">" + example->d_name +  "</a></p>";
        }
        else if (std::string(example->d_name) == ".."){
            if (root == "/"){
                ret += "<p><a href=\"http://" + host + ":" + port + root + "\">" + example->d_name +  "</a></p>";
            }
            else{
                tmp_root = root.substr(0, root.find_last_of('/'));
                ret += "<p><a href=\"http://" + host + ":" + port + tmp_root + "\">" + example->d_name +  "</a></p>";
            }
        }
        else
            ret += "<p><a href=\"http://" + host + ":" + port + root + "/" + example->d_name + "\">" + example->d_name +  "</a></p>";
	}
    ret += "</body></html>";
    closedir(dir);
	return ret;
}

void
dir_listing_response(const std::string &path, const std::string &root, Connection &connection){
    std::string ret = "HTTP/1.1 ";
    std::string tmp;

    tmp = status_to_text(200);
	ret += tmp + "\r\n";
    ret += "Host: " + connection.getHost() + ":" + itos(connection.getPort());
    ret += "Content-type: text/html\r\n";

    tmp = html_from_dir(path, root, connection.getHost(), itos(connection.getPort()));
    if (tmp == ""){
        http_response(403, connection);
        return ;
    }
    ret += "Content-length: " + itos(tmp.size()) + "\r\n\r\n";
    ret += tmp + "\r\n\r\n";

	connection.setResponse(ret);
    connection.setStatus(READY);
    return ;
}
