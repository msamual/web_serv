/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:20:51 by sgath             #+#    #+#             */
/*   Updated: 2021/12/15 15:42:22 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

int		main(int ac, char **av)
{
	std::vector<t_server>	config;
	std::ostream 			*log;

	try
	{
		config = parse_config(ac, av);
		cgi(config[0], "cgi_bin/script.py");
		log = open_log_file(ac, av);
		Server	server(config, log);

		server.start();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}