#include "shell.h"

/**
 * _check_stat_environ - this function checks the token against
 *                       stat structure and environ struct
 * @buff: the buffer
 * @argv: the argv
 * Return: pointer to the getline data
 */
char *_check_stat_environ(char *buff, char **argv)
{
	int i = 0;
	char *token = NULL, *key = "PATH", *path = NULL, **env_cpy = NULL;

	if (strlen(argv[0]) <= 1)
		return ("incomplete");
	if (argv[0][0] == '/' && stat(buff, &st) == 0)
	{
		_execve(argv);
		return ("done");
	}
	while (environ[i])
		i++;
	env_cpy = malloc(sizeof(char *) * i);
	for (i = 0; environ[i]; i++)
		env_cpy[i] = strdup(environ[i]);
	env_cpy[i] = NULL, i = 0;
	while (env_cpy[i])
	{
		token = strtok(env_cpy[i++], "=");
		if (strcmp(key, token) == 0)
		{
			env_cpy = NULL;
			break;
		}
	}
	token = strtok(NULL, "\0"), token = strtok(token, ":");
	while (token != NULL)
	{
		path = malloc(sizeof(char) * (strlen(token) + strlen(buff) + 1));
		strcat(path, token), strcat(path, "/"), strcat(path, buff);
		if (stat(path, &st) == 0)
		{
			argv[0] = strdup(path);
			_execve(argv),  env_cpy = NULL,  path = NULL;
			break;
		}
		token = strtok(NULL, ":");
	}
	env_cpy = NULL,  path = NULL, free(env_cpy), free(path);
	return ("done");
}
