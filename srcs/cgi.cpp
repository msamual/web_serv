#include "CgiClass.hpp"

int
cgi(const t_server &server, Request &request, Connection &connection)
{
//    if (!is_file(request.getPath().c_str())){
//        http_response(404, connection);
//		return (-1);
//    }
	CgiClass test(server, request, connection);
	try {
		test.start();
	}
	catch (std::invalid_argument &e) {
        http_response(404, connection);
		return (-1);
	}
    int InPipe[2], OutPipe[2];
	
	if (pipe(InPipe) != 0 || pipe(OutPipe) != 0){
        http_response(500, connection);
		return (-1);
    }
	// Duplicate stdin and stdout request.getPath() descriptors
	int OldStdIn = dup(fileno(stdin));
	int OldStdOut = dup(fileno(stdout));

	// Duplicate end of pipe to stdout and stdin request.getPath() descriptors
	if ((dup2(OutPipe[1], fileno(stdout)) == -1) || (dup2(InPipe[0], fileno(stdin)) == -1)){
        http_response(500, connection);
		return -1;
	}
    close(OutPipe[1]);
    close(InPipe[0]);

    int child_pid = fork();
    if (child_pid == 0){//in child
        execve(test.argv[0], (char *const *)test.argv, (char *const *)test.env);
        exit(0);
    }

    dup2(OldStdIn, fileno(stdin));
	dup2(OldStdOut, fileno(stdout));
    close(OldStdIn);
	close(OldStdOut);

	if (request.getMethod() == "POST")
	{
		const std::string &body = request.getBody();
		write(InPipe[1], body.c_str(), body.size());
	}
    //while (1)
	// {
	// 	// Читаем ответ от дочернего процесса
	// 	char bufferOut[100000];
	// 	int n = read(OutPipe[0], bufferOut, 100000);
	// 	if (n > 0)
	// 	{
	// 		//Выводим ответ на экран
	// 		fwrite(bufferOut, 1, n, stdout);
	// 		fflush(stdout);
	// 	}
	// 	//Если дочерний процесс завершился, то завершаем и родительский процесс
	// 	int status;
	// 	if (waitpid(child_pid, &status, WNOHANG) > 0)
	// 		break;
	// }
	close(InPipe[1]);
    return OutPipe[0];
}
