#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * which - Returns a char pointer to the location where the desired executable
 * was found.
 * @argv: Pointer to the argv array.
 *
 * Return: char pointer to the found executable or NULL on failure.
 */
char *which(char *argv)
{
	char *pathstring = NULL;
	char *file_in_dir;
	struct stat sb;
	DIR *curr_dir;
	struct dirent *file;
	char *token;

	pathstring = find_path(pathstring);
	if (pathstring == NULL)
		return (NULL);
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

/**
 * find_path - Assigns the current path to pathstring.
 * @pathstring: The string pointer to fill with the pathstring.
 *
 * Return: String for pathstring.
 */

char *find_path(char *pathstring)
{
	char *tmp_env = NULL;
	char *token = NULL;
	int i = 0;
	int found = 0;
	int path1_found = 0;

	while (environ[i] != NULL)
	{
		tmp_env = strdup(environ[i]);
		if (strcmp(tmp_env, "PATH=") == 0)
		{
			free(tmp_env);
			return (NULL);
		}
		token = strtok(tmp_env, "=");
		if (strcmp(token, "PATH") == 0)
		{
			pathstring = strdup(strtok(NULL, "="));
			found = 1;
		}
		if (strcmp(token, "PATH1") == 0)
			path1_found = 1;
		i++;
		free(tmp_env);
	}
	if (found == 1 && path1_found == 0)
		return (pathstring);
	else
		return (NULL);
}
