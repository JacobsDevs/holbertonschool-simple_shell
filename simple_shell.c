#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "main.h"

extern char **environ;

/**
 * main - Main shell process.  Prompts the user for input and then uses
 * builds an argument list, forks and uses execve to execute the desired
 * command.
 *
 * Return: 0 on successful exit.
 */

int main(void)
{
	pid_t child;
	char *input;
	char *buffer;
	size_t buffer_size = 64;
	char *argv[4];
	struct stat sb;

	while (1)
	{
		printf("$ ");
		input = malloc(sizeof(char) * buffer_size);
		getline(&input, &buffer_size, stdin);
		if (strcmp(input, "exit\n") == 0)
		{
			printf("Exiting\n");
			break;
		}
		build_args(input, argv);
		if (stat(argv[0], &sb) == -1)
		{
			printf("Not found: %s\n", argv[0]);
			continue;
		}
		child = fork();
		if (child == -1)
			printf("Failed to start child\n");
		if (child == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
				printf("Unable to exec\n");
			return (0);
		}
		else
		{
			wait(&child);
		}
		clean_args(argv);
	}
	exit(0);
}

/**
 * build_args - Build the argv list from the users input.
 * @input: String the user inputted to the terminal
 * @argv: The array of string arguments to build.
 */
void build_args(char *input, char *argv[])
{
	int i = 0;
	char *token;

	token = strtok(input, "\n");
	token = strtok(token, " ");
	while (token != NULL)
	{
		argv[i] = malloc(strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
}

/**
 * clean_args - Run after the main loop to clear out the args and prepare
 * for a new set of args.
 * @args: The array of string arguments to clear.
 */

void clean_args(char *args[])
{
	int i = 0;

	while (args[i] != NULL)
	{
		args[i] = "";
		i++;
	}
	/*print_args(args);*/
}

/**
 * print_args - A utility function to check the contents of the args list,
 * used for debugging.
 * @args: The array of string arguments to print.
 */
void print_args(char *args[])
{
	int i = 0;

	while (args[i] != NULL)
	{
		printf("arg %d = %s\n", i, args[i]);
		i++;
	}
}
