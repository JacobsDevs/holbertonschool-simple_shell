#ifndef MAIN_H
#define MAIN_H

extern char **environ;

char **malloc_argv(int count);
void clean_argv(char **argv, int count);
int get_input(char **argv);
char *which(char *argv);
void print_environ(void);

#endif
