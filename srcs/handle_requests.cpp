//
// Created by Mitchel Samual on 12/7/21.
//

#include "../includes/Webserv.hpp"

void    handle_requests(Connection& conn, std::ostream& out)
{
    out << "send" << std::endl;
    conn.setResponse("HTTP/1.1 200 OK\r\n\r\n<!DOCTYPE html>\n<html>\n<head>\n<title>Example</title>\n</head>\n<body>\n<p>Yaroslav KUKURUZA.</p>\n</body>\n</html>");
    conn.setStatus(READY);
}