#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include "../include/cmd.h"

int main(int argc, char *argv[]) {
	DIR *dir;
	struct dirent *entry;

	if(argc != 2)
		return 0;

	if ((dir = opendir("/bin/")) == NULL)
		perror("opendir() error");
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (my_strcmp(entry->d_name, argv[1]) == 0)
				printf("%s is in /bin\n",argv[1]);
		}
		closedir(dir);
	}
	
	if ((dir = opendir("/usr/bin/")) == NULL)
		perror("opendir() error");
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (my_strcmp(entry->d_name, argv[1]) == 0)
				printf("%s is in /usr/bin\n", argv[1]);
		}
		closedir(dir);
	}

	return 0;
}