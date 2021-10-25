/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:20:53 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 09:21:48 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"

int	my_strcmp(const char *s1, const char *s2)
{
	while ((unsigned char)*s1 == (unsigned char)*s2)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*get_value_from_envlist(char *key, t_env_list *env_list)
{
	t_env_node	*cur_envnode;
	char		*value;

	cur_envnode = env_list->head;
	value = NULL;
	while (cur_envnode != NULL)
	{
		if (my_strcmp(key, cur_envnode->key) == 0)
		{
			value = ft_strdup(cur_envnode->value);
			return (value);
		}
		cur_envnode = cur_envnode->next;
	}
	return (NULL);
}

//input: "hello $TEST"
//output: 1->exist, 0->nah
int	envvar_exist(char *word, int *i, int *j)
{
	*i = 0;
	while (word[*i] != '\0')
	{
		if (word[*i] == '\\' && word[*i + 1] != '\0')
		{
			i += 2;
			continue ;
		}
		if (word[*i] == '$')
		{
			*j = *i + 1;
			while (word[*j] != '\0' && word[*j] != ' '
				&& word[*j] != '$' && word[*j] != '\\' && word[*j] != ',')
				(*j)++;
			if (*j > *i + 1)
				return (1);
		}
		(*i)++;
	}
	return (0);
}

//input: "$NAME"
//output:"takuya"
char	*get_env_value(char *word, t_env_list *env_list)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	value = NULL;
	if (envvar_exist(word, &i, &j))
	{
		key = ft_substr(word, i + 1, j - (i + 1));
		value = get_value_from_envlist(key, env_list);
		free(key);
		if (value == NULL)
			value = ft_strdup("");
	}
	return (value);
}

//input: "ABC $TEST 123"
//output:"ABC hello   world 123"
char	*make_new_word(char *word, char *env_value)
{
	char	*new_word;
	int		env_i;
	int		env_j;
	int		new_word_len;

	envvar_exist(word, &env_i, &env_j);
	new_word_len = ft_strlen(word) + (ft_strlen(env_value) - (env_j - env_i));
	new_word = (char *)malloc(sizeof(char) * new_word_len + 1);
	ft_strlcpy(new_word, word, new_word_len + 1);
	ft_strlcpy(new_word + env_i, env_value, new_word_len + 1);
	ft_strlcpy(new_word + (env_i + ft_strlen(env_value)),
		word + env_j, new_word_len + 1);
	return (new_word);
}
