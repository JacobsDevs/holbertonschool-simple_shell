#include "main.h"
#include <stdlib.h>
#include <stdio.h>
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
