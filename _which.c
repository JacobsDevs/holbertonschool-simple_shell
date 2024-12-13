#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int _while(int argc, char **argv)
{
	const char *path = "PATH";
	char *paths = getenv(path);
	char *token;
	char *file_in_dir;
	struct stat sb;
	DIR *curr_dir;
	struct dirent *file;
	(void)argc;

	token = strtok(paths, ":");
	while (token != NULL)
	{
		file_in_dir = malloc((strlen(token)) + (strlen(argv[1])) + 2);
		sprintf(file_in_dir, "%s/%s", token, argv[1]);
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
			/*If it exists*/

			if (stat(file_in_dir, &sb) == 0)
			{
				/*print out the directory*/

				printf("%s\n", file_in_dir);
				return (1);
			}
		}
		closedir(curr_dir);
		free(file_in_dir);
		token = strtok(NULL, ":");
	}
	return (0);
}
