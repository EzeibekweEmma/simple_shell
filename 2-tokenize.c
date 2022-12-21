#include "shell.h"

/**
 * _tokenize - this is the prompt and getline function for simple shell
 * @buff: environment variable
 * Return: pointer to the getline data
 */
char *_tokenize(char *buff)
{
	char *tokens, **argv = NULL, *delimeter = " \n";
	int i = 0;

	argv = malloc((sizeof(char) * strlen(buff)) * 2);
	tokens = strtok(buff, delimeter);
	while (tokens != NULL)
	{
		argv[i] = tokens;
		tokens = strtok(NULL, delimeter);
		i++;
	}
	/*call stat_env function*/
	_check_stat_environ(buff, argv);

	tokens = NULL;
	delimeter = NULL;
	free(argv);
	return ("done");
}
