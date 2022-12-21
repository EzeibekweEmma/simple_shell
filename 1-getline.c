#include "shell.h"

/**
 * _getline - this is the prompt and getline function for simple shell
 * Return: pointer to the getline data
 */
char *_getline(void)
{
	size_t n = 10;
	char *buff = NULL, *copy_of_buff = NULL,  *token, *delimeter = " \n";

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
			{
				copy_of_buff = strdup(buff);
				token = strtok(copy_of_buff, delimeter);
				if (strcmp(token, "exit") == 0)
				{
					buff = NULL, free(buff);
					copy_of_buff = NULL;
					delimeter = NULL;
					token = NULL;
					return ("done");
				}
				_tokenize(buff);
				copy_of_buff = NULL;
				token = NULL;
			}
		}
		buff = NULL, free(buff);
	}
}
