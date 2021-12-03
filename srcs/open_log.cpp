//
// Created by Mitchel Samual on 12/3/21.
//

#include <fstream>
#include <iostream>

std::ostream* open_log_file(int ac, char **av)
{
	std::ofstream *res = new std::ofstream;

	if (ac > 2)
	{
		res->open(av[2]);
		if (!res->is_open())
		{
			std::cout << "Cant open logfile. using STDOUT.";
			return &std::cout;
		}
	}
	else
		return &std::cout;
	return res;
}