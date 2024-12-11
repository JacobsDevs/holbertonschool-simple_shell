#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(void)
{
	pid_t child;
	char *input;
	char *buffer;
	size_t buffer_size = 64;
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};
	char *token;

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
		child = fork();
		if (child == -1)
			printf("Failed to start child\n");
		if (child == 0)
		{
			execve(token, argv, NULL);
			return (0);
		}
		else 
		{
			wait(&child);
		}
	}
	exit (0);
}
