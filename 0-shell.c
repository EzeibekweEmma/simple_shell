#include "shell.h"

/**
 * main - this is the main function call for our simple shell
 * @ac: arguement counts
 * @argv: arguement vectors
 * Return: 0 if succesful
 */
int main(int ac, char **argv)
{
	(void) ac;

	_getline(argv[0]);
	return (0);
}
