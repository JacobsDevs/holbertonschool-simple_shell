#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char *which(char *argv)
{
	char *pathstring = NULL;
	char *file_in_dir;
	struct stat sb;
	DIR *curr_dir;
	struct dirent *file;
	int i = 0;
	char *token;
	char *tmp_env = NULL;

	while (environ[i] != NULL)
	{
		tmp_env = strdup(environ[i]);
		token = strtok(tmp_env, "=");
		if (strcmp(token, "PATH") == 0)
		{
			pathstring = strdup(strtok(NULL, "="));
		}
		i++;
		free(tmp_env);
	}
	token = strtok(pathstring, ":");
	while (token != NULL)
	{
		file_in_dir = malloc((strlen(token)) + (strlen(argv)) + 2);
		sprintf(file_in_dir, "%s/%s", token, argv);
		curr_dir = opendir(token);
		if (curr_dir == NULL)
		{
			closedir(curr_dir);
			free(file_in_dir);
			token = strtok(NULL, ":");
			continue;
		}
		while ((file = readdir(curr_dir)) != NULL)
		{
			if (stat(file_in_dir, &sb) == 0)
			{
				closedir(curr_dir);
				free(pathstring);
				return (file_in_dir);
			}
		}
		closedir(curr_dir);
		free(file_in_dir);
		token = strtok(NULL, ":");
	}
	free(pathstring);
	return (NULL);
}
