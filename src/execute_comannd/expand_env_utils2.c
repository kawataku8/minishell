/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:24:15 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 13:57:25 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"

void	free_splitstr(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

//input	  	:word = "12$TEST$USER"; env_value = "hello world"
//output	:new_tokenlist = "12hello"->"world$USER"
//description: 
//normal expand env val in field word
t_list	*make_new_tokens(char *word, char *env_value)
{
	t_list	*new_tokenlist;
	t_token	*new_token;
	char	*new_word;
	char	**split_newword;
	int		l;

	new_tokenlist = NULL;
	new_word = make_new_word(word, env_value);
	split_newword = ft_split(new_word, ' ');
	l = 0;
	while (split_newword[l] != NULL)
	{
		new_token = (t_token *)malloc(sizeof(t_token));
		new_token->type = STR;
		new_token->word = ft_strdup(split_newword[l++]);
		ft_lstadd_back(&new_tokenlist, ft_lstnew((void *)new_token));
	}
	free(new_word);
	free_splitstr(split_newword);
	return (new_tokenlist);
}

//input: "$NAME"
//output: "oda"->"joe"
t_list	*expand_env_in_token(t_list *token, char *env_value, int flag_dquote)
{
	t_list	*new_tokenlist;
	t_token	*new_token;
	char	*new_word;

	new_tokenlist = NULL;
	if (flag_dquote)
	{
		new_word = make_new_word(((t_token *)token->content)->word, env_value);
		new_token = (t_token *)malloc(sizeof(t_token));
		new_token->type = STR;
		new_token->word = new_word;
		ft_lstadd_back(&new_tokenlist, ft_lstnew((void *)new_token));
	}
	else
		new_tokenlist = make_new_tokens(((t_token *)token->content)->word,
				env_value);
	return (new_tokenlist);
}

void	flag_init(int *flag_dquote, int *flag_squote)
{
	*flag_dquote = 0;
	*flag_squote = 0;
}
