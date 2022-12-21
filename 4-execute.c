#include "shell.h"

/**
 * _execve - this is the prompt and getline function for simple shell
 * @argv: environment variable
 * Return: pointer to the getline data
 */
char *_execve(char **argv)
{
	int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return ("Error");
	}
	if (child_pid == 0)
	{
		execve(argv[0], argv, NULL);
		sleep(4);

	}
	wait(&status);
	kill(child_pid, SIGKILL);
	return ("Done");
}

