#include "shell.h"

/**
 * _check_stat_environ - this function checks the token against
 *                       stat structure and environ struct
 * @av: file name
 * @buff: the buffer
 * @argv: the argv
 * Return: pointer to the getline data
 */
char *_check_stat_environ(char *av, char *buff, char **argv)
{
	if (strlen(argv[0]) <= 1)
		return ("incomplete");
	if (argv[0][0] == '/' && stat(buff, &st) == 0 && argv[1] == NULL)
	{
		_execve(argv);
		return ("done");
	}
	printf("%s : No such file or directory\n", av);
	return ("done");
}
