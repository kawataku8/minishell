/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 09:27:31 by stakabay          #+#    #+#             */
/*   Updated: 2021/06/26 12:06:43 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

/*
**	env_arrを作る
**	①Keyが_のみの場合は無視（printしない）
**	②値がない場合はKeyのみを文字列として入れる
**	③Key="value"の形にして文字列を作って入れる
**		※"$\はそのまま文字列にして入れるとプリントできないので直前にバックスラッシュを追加する。
**	env_arrを辞書順にソートする
**	プリントする
*/

void	print_env_arr(char **env_arr)
{
	int	i;

	i = 0;
	while (env_arr[i])
	{
		put_string_fd("declare -x ", STD_OUT);
		ft_putendl_fd(env_arr[i], STD_OUT);
		i++;
	}
}

char	**malloc_arr(t_env_list *list)
{
	char		**env_arr;
	int			envcount;
	t_env_node	*node;

	envcount = 0;
	node = list->head;
	while (node != NULL)
	{
		envcount++;
		node = node->next;
	}
	env_arr = malloc(sizeof(char *) * envcount + 1);
	if (env_arr == NULL)
		exit(malloc_error());
	return (env_arr);
}

char	**make_env_arr(t_env_list *list)
{
	t_env_node	*node;
	int			i;
	char		**env_arr;

	i = 0;
	env_arr = malloc_arr(list);
	node = list->head;
	merge_sort(&node);
	while (node != NULL)
	{
		if (ft_strncmp(node->key, "_", 2))
		{
			env_arr[i] = ft_strdup(node->key);
			if (env_arr[i] == NULL)
				exit(malloc_error());
			if (node->value)
			{
				env_arr[i] = ft_strjoin(env_arr[i], "=\"");
				env_arr[i] = ft_strjoin(env_arr[i], node->value);
				env_arr[i] = ft_strjoin(env_arr[i], "\"");
				if (!env_arr[i])
					exit(malloc_error());
			}
			i++;
		}
		node = node->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	export_env_list(t_env_list *list)
{
	char	**env_arr;
	char	**ptr;

	env_arr = make_env_arr(list);
	print_env_arr(env_arr);
	ptr = env_arr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(env_arr);
}