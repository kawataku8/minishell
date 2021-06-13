#include "../include/command.h"

/***********************************
 * CD
***********************************/


// 	1. to home directory >> no args || "--"
// 	2. to previous directory >> only'-'
// 		bash: cd: OLDPWD not set
// 	3. replace with home directory path >> '~' || !arg

char		*set_path(char **argv, int argc, t_env_list *list)
{
	t_env_node	*node;
	char		*path;
	char		*ptr;

	if (argc == 1 || !ft_strncmp(argv[1], "--", 2))
	{
		node = serch_nodes(list, "HOME");
		path = ft_strdup(node->value);
	}
	else if (!ft_strncmp(argv[1], "-", 1))
	{
		if ((node = serch_nodes(list, "OLDPWD")) == NULL)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		path = ft_strdup(node->value);
	}
	else if (argv[1][0] == '~')
	{
		node = serch_nodes(list, "HOME");
		argv[1]++;
		path = ft_strjoin(node->value, argv[1]);
	}
	else
		path = ft_strdup(argv[1]);

	return(path);
}

int			is_valid_arg(char **argv, int argc, t_env_list *list)
{
	//more than 2 arguments
	if (argc >= 3)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (0);
	}
	//no arg with no HOME env
	if (argc == 1 && !serch_nodes(list, "HOME"))
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (0);
	}
	return (1);
}

int		ft_cd(int argc, char **argv, t_env_list *list)
{
	char		*path;
	t_env_node	*node;
	t_env_node	*ndptr;

	//error handling of no arguments or invalid args
	if (!is_valid_arg(argv, argc, list))
		return(0);
	path = set_path(argv, argc, list);
	if (chdir(path) == -1)
		return (0);
	node = serch_nodes(list, "PWD");
	if ((ndptr = serch_nodes(list, "OLDPWD")) == NULL)
	{
		ndptr = make_node("OLDPWD", node->value);
		insert_end(list, ndptr);
	}
	else
		ndptr->value = ft_strdup(node->value);	
	node->value = ft_strdup(path);
	// set_oldpwd();
	// ft_export();
	// free(path)	
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_env_list	env_list;
	t_env_node	*node;
	t_env_node	*ndptr;
	char		*keybuf;
	char		*valuebuf;
	char		*ptr;

	while (*envp)
	{
		ptr = ft_strchr(*envp, '=');
		keybuf = ft_substr(*envp, 0, ptr - *envp);
		valuebuf = ft_strdup(*envp + (ptr - *envp + 1));
		node = make_node(keybuf, valuebuf);
		//printf("declare -x %s=", node->key);
		//printf("%s\n", node->value);
		insert_end(&env_list, node);
		node = node->next;
		envp++;
	}
	if (argc >= 2)
	{
		argv++;
		argc--;
	}	
	printf("befor cwd :%s\n", getcwd(NULL, 0));
	node = serch_nodes(&env_list, "PWD");
	printf("befor PWD :%s\n", node->value);
	if ((node = serch_nodes(&env_list, "OLDPWD")) != NULL)
		printf("befor OLDPWD :%s\n", node->value);
	ft_cd(argv, argc, &env_list);
	printf("after cwd :%s\n", getcwd(NULL, 0));
	node = serch_nodes(&env_list, "PWD");
	printf("after PWD :%s\n", node->value);
	if ((node = serch_nodes(&env_list, "OLDPWD")) != NULL)
		printf("after OLDPWD :%s\n", node->value);
	return (0);
}
