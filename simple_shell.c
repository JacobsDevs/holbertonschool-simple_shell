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
	char *argv[] = {NULL};
	char *envp[] = {"PATH=/home/jacob/.local/share/mise/installs/ruby/3.3.6/bin:/home/jacob/.local/share/mise/installs/node/22.11.0/bin:./bin:/home/jacob/.local/bin:/home/jacob/.local/share/omakub/bin:/home/jacob/.local/bin:./bin:/home/jacob/.local/bin:/home/jacob/.local/share/omakub/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin", NULL};
	char *token;
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
		if (stat(token, &sb) == -1)
		{
			printf("Not found: %s\n", token);
			continue;
		}
		child = fork();
		if (child == -1)
			printf("Failed to start child\n");
		if (child == 0)
		{
			execve(token, argv, environ);
			return (0);
		}
		else 
		{
			wait(&child);
		}
	}
	exit (0);
}
