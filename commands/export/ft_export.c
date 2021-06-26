/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 22:25:20 by stakabay          #+#    #+#             */
/*   Updated: 2021/06/26 12:32:19 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

/*
**--export--
**①引数なし　⇨　環境変数一覧の出力
**②引数あり　⇨　環境変数の登録
**
**②
**新しいノードを作成し、引数を分解して入力。
**引数が複数ある場合は登録する。
**既存のkeyと被り、value登録あり　⇨　exportを無視し、変化なし。
**被りあり、valueなし　⇨　新valueを登録。
*/

t_env_node	*make_newnode_from_arg(char *argv, t_env_node *node)
{
	char		*ptr;
	char		*keybuf;
	char		*valuebuf;

	ptr = ft_strchr(argv, '=');
	if (ptr != NULL)
	{
		keybuf = ft_substr(argv, 0, ptr - argv);
		valuebuf = ft_strdup(argv + (ptr - argv + 1));
		node = make_env_node(keybuf, valuebuf);
		if (!keybuf || !valuebuf || !node)
			exit(malloc_error());
	}
	else
	{
		keybuf = ft_strdup(argv);
		valuebuf = NULL;
		node = make_env_node(keybuf, valuebuf);
		if (!keybuf || !node)
			exit(malloc_error());
	}
	free(keybuf);
	free(valuebuf);
	return (node);
}

void	export_identifier_error(t_env_node *node, int *renum, char *argv)
{
	put_string_fd("minishell: export: \'", STD_ERR);
	put_string_fd(argv, STD_ERR);
	ft_putendl_fd("\': not a valid identifier", STD_ERR);
	free(node->key);
	free(node->value);
	free(node);
	*renum = ERROR;
}

void	insert_node_to_list(t_env_list *list, t_env_node *node)
{
	t_env_node	*ndptr;

	ndptr = serch_nodes(list, node->key);
	if (ndptr == NULL)
		insert_end(list, node);
	else if (!ndptr->value && node->value)
	{
		ndptr->value = ft_strdup(node->value);
		if (ndptr->value == NULL)
			exit(malloc_error());
	}
	free(node);
}

int	ft_export(char **argv, t_env_list *list)
{
	t_env_node	*node;
	int			renum;
	int			i;

	i = 1;
	renum = SUCCESS;
	if (!argv[1])
		export_env_list(list);
	while (argv[i])
	{
		node = make_newnode_from_arg(argv[i], node);
		if ((is_valid_env_key(node->key)) == FALSE)
			export_identifier_error(node, &renum, *argv);
		else
			insert_node_to_list(list, node);
		i++;
	}
	return (renum);
}


// int		main(int argc, char **argv, char **envp)
// {
// 	t_env_list	env_list;
// 	t_env_node	*ndptr;
// 	t_env_node	*node;
// 	char		*ptr;
// 	char		*keybuf;
// 	char		*valuebuf;

// 	while (*envp)
// 	{
// 		ptr = ft_strchr(*envp, '=');
// 		keybuf = ft_substr(*envp, 0, ptr - *envp);
// 		valuebuf = ft_strdup(*envp + (ptr - *envp + 1));
// 		node = make_env_node(keybuf, valuebuf);
// 		//printf("declare -x %s=", node->key);
// 		//printf("%s\n", node->value);
// 		insert_end(&env_list, node);
// 		node = node->next;
// 		envp++;
// 	}
// 	if (argc == 1)
// 		return (0);
// 	argv++;
// 	ft_export(argv, &env_list);

// 	if (argv[1])
// 	{
// 		ndptr = env_list.head;
// 		while (ndptr)
// 		{
// 			printf("%s=%s\n", ndptr->key,ndptr->value);
// 			ndptr = ndptr->next;
// 		}
// 	}
// 	return (0);
// }
