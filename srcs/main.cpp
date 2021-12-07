/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:20:51 by sgath             #+#    #+#             */
/*   Updated: 2021/12/04 16:16:08 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

std::string     parsingConf(char *str)
{
    return str;
}

int		main(int ac, char **av)
{
	std::vector<t_server>	config;
	std::ostream 			*log;

	try
	{
		config = parse_config(ac, av);
		log = open_log_file(ac, av);
		Server	server(config, OLD_set_error_pages(config), log);

		server.start();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}