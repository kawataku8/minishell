#include "../../include/cmd.h"

char *make_cmd_path(char *target_dir, char *cmd_name)
{
	DIR *dir;
	struct dirent *entry;
	char *res;

	res = NULL;
	if ((dir = opendir(target_dir)) == NULL)
	{
		perror("opendir() error");
		return (res);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (my_strcmp(entry->d_name, cmd_name) == 0)
			res = ft_strjoin(target_dir, cmd_name);
	}
	closedir(dir);
	return (res);
}

// find an absolute path of command
void find_abscmd_path(char **cmd_argv)
{
	char *abs_cmd_path;

	abs_cmd_path = NULL;
	// check cmd_argv[0][0] is "/"
	if (cmd_argv[0][0] == 47)
		return ;	
	abs_cmd_path = make_cmd_path("/bin/", cmd_argv[0]);
	if (abs_cmd_path == NULL)
		abs_cmd_path = make_cmd_path("/usr/bin/", cmd_argv[0]);
	if (abs_cmd_path == NULL)
		return ;
	free(cmd_argv[0]);
	cmd_argv[0] = abs_cmd_path;
}

// TEST
// gcc find_cmd_path.c expand_env.c  ../../libft/libft.a
// int main(void)
// {
// 	char **argv = ft_split("mkdir", ' ');

// 	for (int i = 0; argv[i] != NULL; i++)
// 	{
// 		printf("%s\n",argv[i]);
// 	}
// 	printf("-------------------------\n");

// 	find_abscmd_path(argv);
// 	for (int i = 0; argv[i] != NULL; i++)
// 	{
// 		printf("%s\n",argv[i]);
// 	}

// 	free_splitstr(argv);
// 	exit(1);
// 	return 0;	
// }