#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>

char *_getline(char *av);
char *_tokenize(char * av, char *buff);
char *_check_stat_environ(char *av, char *buff, char **argv);
char *_execve(char **argv);

struct stat st;
extern char **environ;

#endif
