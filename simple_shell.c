#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "main.h"

#define MAX_STRING_LENGTH 20


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
	char **argv = NULL;
	struct stat sb;
	int count = 3;
	int running = 1;

	while (running == 1)
	{
		argv = malloc_argv(count);
		if (argv == NULL)
		{
			printf("Failed to malloc argv\n");
			return (1);
		}
		if (isatty(0) == 0)
		{
			if (get_input(argv) == 1)
			{
				clean_argv(argv, count);
				break;
			}
		}
		else
		{
			printf("$ ");
			get_input(argv);
		}
		if (stat(argv[0], &sb) == -1)
		{
			printf("%s: command not found\n", argv[0]);
			clean_argv(argv, count);
			continue;
		}
		if (strcmp(argv[0], "exit") == 0)
			execve(argv[0], argv, environ);
		child = fork();
		if (child == -1)
			printf("Failed to Fork");
		if (child == 0)
			execve(argv[0], argv, environ);
		else
		{
			wait(&child);
			clean_argv(argv, count);
		}
	}
	return (0);
}

/**
 * malloc_argv - Allocates memory to the argv pointer pointer
 * @count: The amount of strings to be stored in argv
 *
 * Return: Pointer to a pointer to argv
 */

char **malloc_argv(int count)
{
	char **args = NULL;
	int i;

	args = (char **)malloc(count * sizeof(char *));
	for (i = 0; i < count; i++)
		args[i] = NULL;
	return (args);
}

/**
 * get_input - Gets input from the user and stores it in argv
 * @argv: Pointer to pointer of argv
 *
 * Return: 0 for success 1 for failure to read line.
 */

int get_input(char **argv)
{
	char *buffer = NULL;
	size_t bsize = 100;
	char *token = NULL;
	int i = 0;

	if (getline(&buffer, &bsize, stdin) == -1)
	{
		free(buffer);
		return (1);
	}
	token = strtok(buffer, "\n");
	token = strtok(token, " ");
	while (token != NULL)
	{
		argv[i] = strdup(token);
		token = strtok(NULL, " ");
		i++;
	}
	free(buffer);
	return (0);
}

/**
 * clean_argv - Frees all memory held by argv
 * @argv: Pointer to a pointer of argv
 * @count: The number of entries to expect in argv
 */

void clean_argv(char **argv, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
