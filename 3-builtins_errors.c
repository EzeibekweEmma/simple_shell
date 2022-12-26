#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables
 *
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(vars->av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(vars);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @vars: variables
 *
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * _env - prints the current environment
 * @vars: struct of variables
 *
 * Return: void.
 */
void _env(vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->env[i]; i++)
	{
		_puts(vars->env[i]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int i, j;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		newenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		newenv[i] = vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}


/**********************************************other builtins******************************************************/






/**
 * add_key - create a new environment variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void add_key(vars_t *vars)
{
	unsigned int i;
	char **newenv;

	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != NULL; i++)
		newenv[i] = vars->env[i];
	newenv[i] = add_value(vars->av[1], vars->av[2]);
	if (newenv[i] == NULL)
	{
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(newenv);
		exit(127);
	}
	newenv[i + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_key(char **env, char *key)
{
	unsigned int i, j, len;

	len = _strlen(key);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
			if (key[j] != env[i][j])
				break;
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, i, j;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	return (num);
}



















/**********************************************error checks******************************************************/




/**
 * print_error - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @msg: message to print out
 *
 * Return: void
 */
void print_error(vars_t *vars, char *msg)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (msg)
	{
		_puts2(msg);
	}
	else
		perror("");
}

/**
 * _puts2 - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void _puts2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts an unsigned int to a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_uitoa(unsigned int count)
{
	char *numstr;
	unsigned int tmp, digits;

	tmp = count;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; count; --digits)
	{
		numstr[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (numstr);
}
