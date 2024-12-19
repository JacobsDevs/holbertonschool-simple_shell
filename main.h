#ifndef MAIN_H
#define MAIN_H

extern char **environ;

typedef struct stat stat_t;
char **malloc_argv(int count);
void clean_argv(char **argv);
int get_input(char **argv);
char *which(char *argv);
void print_environ(char **argv);
void run_exit(char **argv, int exit_status);
void search_for_function(char **argv, stat_t sb);
char *find_path(char *pathstring);
void invalid_path(char **argv);

#endif
