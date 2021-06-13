#include "command.h"

//環境変数の鍵は頭は数字はだめ。
//また、全体で数字とアルファベット以外は_をのぞいてだめ
int		is_valid_env_key(char *key)
{
	if (!key)
		return (FALSE);
	if ('0' <= *key && *key <= '9')
		return (FALSE);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (FALSE);
		++key;
	}
	return (TRUE);
}

int		ft_unset(char **argv, t_env_list *list)
{
	t_env_node	*node;
	int			renum;

	renum = SUCCESS;
	while (*argv)
	{
		if (!is_valid_env_key(*argv))
		{
			put_string_fd("minishell: export: \'", STD_ERR);
			put_string_fd(*argv, STD_ERR);
			put_string_fd("\': not a valid identifier\n", STD_ERR);
			renum = FALSE;
		}
		else
		{
			node = serch_nodes(list, *argv);
			if (node)
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
				free(node);
			}
		}
		argv++;
	}
	return (renum);
}

int main(int argc, char **argv, char **envp)
{
	t_env_list	env_list;
	t_env_node	*node;
	char		*keybuf;
	char		*valuebuf;
	char		*ptr;

	while (*envp)
	{
		ptr = ft_strchr(*envp, '=');
		keybuf = ft_substr(*envp, 0, ptr - *envp);
		valuebuf = ft_strdup(*envp + (ptr - *envp + 1));
		node = make_node(keybuf, valuebuf);
		// printf("declare -x %s=", node->key);
		//printf("%s\n", node->value);
		insert_end(&env_list, node);
		node = node->next;
		envp++;
	}

	node = env_list.head;
	printf("=before unset=======\n");
	while (node)
	{
		printf("%s\n", node->key);
		node = node->next;
	}

	argv++;
	ft_unset(argv, &env_list);

	node = env_list.head;
	printf("=after unset=======\n");
	while (node)
	{
		printf("%s\n", node->key);
		node = node->next;
	}
	return (0);
}