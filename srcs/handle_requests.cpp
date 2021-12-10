//
// Created by Mitchel Samual on 12/7/21.
//

#include "../includes/Webserv.hpp"

void    handle_requests(Connection& conn, std::ostream& out)
{
	out << "";
    conn.setResponse("HTTP/1.1 200 OK\r\nHost: localhost:8081\r\nContent-type: text/html\r\nContent-length: 108\r\n\r\n<!DOCTYPE html>\n<html>\n<head>\n<title>Example</title>\n</head>\n<body>\n<p>Yaroslav KUKURUZA.</p>\n</body>\n</html>\r\n\r\n");
	conn.clear_request();
    conn.setStatus(READY);
}