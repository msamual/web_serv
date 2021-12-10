#include <Webserv.hpp>

static const int ENV_LEN = 6;

void
print_env(const char **env){
    for (int i = 0; env[i] != NULL; ++i){
        std::cout << env[i] << std::endl;
    }
    return ;
}

int
cgi(t_server &server, const char *file)
{
    static const char *env[ENV_LEN] = {
        (std::string("HTTP_HOST=") + server.host).data(),
        (std::string("Content-Length=") + "12").data(),
        ("Server_Name="+server.names[0]).data(),
        "VARIABLE2=sisa",
        "VARIABLE3=sosisa",
        NULL,
    };
    static const char *argv[5] = {
        server.locations.back().default_file.c_str(),
        file,
        "VARIABLE2",
        "VARIABLE3",
        NULL
    };

    std::cout << "SERVER SIDE :\n";
    print_env(env);
    std::cout << "CLIENT SIDE :\n";

    int InPipe[2], OutPipe[2];
	
	if (pipe(InPipe) != 0 || pipe(OutPipe) != 0){
        throw(std::runtime_error("pipes error"));
    }

	// Duplicate stdin and stdout file descriptors
	int OldStdIn = dup(fileno(stdin));
	int OldStdOut = dup(fileno(stdout));

	// Duplicate end of pipe to stdout and stdin file descriptors
	if ((dup2(OutPipe[1], fileno(stdout)) == -1) || (dup2(InPipe[0], fileno(stdin)) == -1))
		return 0;
    close(OutPipe[1]);
    close(InPipe[0]);

    int child_pid = fork();
    if (child_pid == 0){//in child
        execve(argv[0], (char *const *)argv, (char *const *)env);
        exit(0);
    }

    dup2(OldStdIn, fileno(stdin));
	dup2(OldStdOut, fileno(stdout));
    close(OldStdIn);
	close(OldStdOut);

    std::string request = "Hello world!";
    write(InPipe[1], request.c_str(), request.size());

    while (1)
	{
		// Читаем ответ от дочернего процесса
		char bufferOut[100000];
		int n = read(OutPipe[0], bufferOut, 100000);
		if (n > 0)
		{
			//Выводим ответ на экран
			fwrite(bufferOut, 1, n, stdout);
			fflush(stdout);
		}

		//Если дочерний процесс завершился, то завершаем и родительский процесс
		int status;
		if (waitpid(child_pid, &status, WNOHANG) > 0)
			break;
	}
    return 0;
}
