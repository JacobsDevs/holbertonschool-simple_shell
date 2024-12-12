#ifndef MAIN_H
#define MAIN_H

extern char **environ;

void clean_args(char *args[]);
void print_args(char *args[]);
void build_args(char *input, char *argv[]);

#endif
