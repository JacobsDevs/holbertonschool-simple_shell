#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

extern char **environ;

int main(void)
{
	pid_t child;
	char *input;
	char *buffer;
	size_t buffer_size = 64;
	char *argv[4];
	int i = 0;
	char *token;
	char *tmp;
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
		if (stat(argv[0], &sb) == -1)
		{
			printf("Not found: %s\n", token);
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
	}
	exit (0);
}
