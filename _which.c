#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

char *which(char *argv)
{
	const char *path = "PATH";
	char *paths = getenv(path);
	char *pathstring = strdup(paths);
	char *token;
	char *file_in_dir;
	struct stat sb;
	DIR *curr_dir;
	struct dirent *file;

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
				return (file_in_dir);
			}
		}
		closedir(curr_dir);
		free(file_in_dir);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
