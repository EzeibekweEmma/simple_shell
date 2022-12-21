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

char *_getline(void);
char *_tokenize(char *buff);
char *_execve(char **argv);
char *_check_stat_environ(char *buff, char **argv);
struct stat st;
extern char **environ;



#endif
