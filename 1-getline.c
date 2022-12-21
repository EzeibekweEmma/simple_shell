#include "shell.h"

/**
 * _getline - this is the prompt and getline function for simple shell
 * @av: file name
 * Return: pointer to the getline data
 */
char *_getline(char *av)
{
	size_t n = 10;
	char *buff = NULL;
/*, *copy_of_buff = NULL,  *token, *delimeter = " \n";*/

	while (1)
	{
		buff = malloc(sizeof(char) * n);
		if (buff != NULL)
		{
			printf("ezra_emma_shell$ ");
			if ((getline(&buff, &n, stdin)) == -1)
				perror("Error with getline");

			if (strlen(buff) <= 1)
			{
				buff = NULL, free(buff);
				continue;
			}
			if (buff != NULL)
				_tokenize(av, buff);
		}
		buff = NULL, free(buff);
	}
}
