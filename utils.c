#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
/**
 * print_environ - Iterates through the environ variable and prints each one to
 * stdout.
 * @argv: Pointer to the argv array.
 */

void print_environ(char **argv)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	clean_argv(argv);
}

/**
 * run_exit - cleans the args in argv and runs exit with exit_status
 * @argv: Pointer to argv array.
 * @exit_status: The exit status to return to the system
 */
void run_exit(char **argv, int exit_status)
{
	clean_argv(argv);
	exit(exit_status);
}

/**
 * invalid_path - exits the program when PATH is not found
 * @argv: Pointer to the argv array.
 */
void invalid_path(char **argv)
{
	fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
	clean_argv(argv);
	exit(127);
}

/**
 * search_for_function - Uses which to locate the function in the PATH env
 * variables.
 * @argv: Pointer to the argv array.
 * @sb: stat struct used to validate file.
 */
void search_for_function(char **argv, stat_t sb)
{
	char *tmp = NULL;

	check_valid_env(argv);
	tmp = which(argv[0]);
	if (tmp == NULL || stat(tmp, &sb) == -1)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		free(tmp);
		clean_argv(argv);
		exit(127);
	}
	else
	{
		free(argv[0]);
		argv[0] = strdup(tmp);
		free(tmp);
	}
}

/**
 * check_valid_env - Looks through the environ to find a valid PATH variable &
 * quits the program if non exists.
 * @argv: Pointer to the argv array.
 */
void check_valid_env(char **argv)
{
	char *tok = NULL;
	char *hold = NULL;
	int j = 0;
	int path_found = 0;

	while (environ[j] != NULL)
	{
		hold = strdup(environ[j]);
		tok = strtok(hold, "=");
		if (strcmp(tok, "PATH") == 0)
			path_found = 1;
		j++;
		free(hold);
	}
	if (path_found == 0)
	{
		printf("Why though?\n");
		invalid_path(argv);
	}
}
