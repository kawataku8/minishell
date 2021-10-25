/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:13:12 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 22:55:25 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/parse.h"

void	free_token(t_list *token)
{
	free(((t_token *)token->content)->word);
	free(token->content);
	free(token);
}

void	flag_quote(t_list *cur_token, int *flag_dquote, int *flag_squote)
{
	if ((((t_token *)cur_token->content)->type) == DQUOTE)
		*flag_dquote ^= 1;
	if ((((t_token *)cur_token->content)->type) == SQUOTE)
		*flag_squote ^= 1;
}

t_list	*make_expanded_tokenlist(t_list *cur_token, t_list *last_token,
char *env_value, int flag_dquote)
{
	t_list	*new_tokenlist;
	t_list	*next_token;

	new_tokenlist = expand_env_in_token(cur_token, env_value, flag_dquote);
	next_token = cur_token->next;
	ft_lstadd_back(&new_tokenlist, next_token);
	free(cur_token);
	if (last_token != NULL)
		last_token->next = new_tokenlist;
	return (new_tokenlist);
}

// //input: "echo"->" "->"hello"->"$NAME"->";"
// //output:"echo"->" "->"hello"->"takuya"->";"
// //t_list->content == t_token
// void	expand_env(t_list *token_list, t_env_list *env_list)
void	expand_env(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int		flag_dquote;
	int		flag_squote;
	char	*env_value;
	t_list	*cur_token;
	t_list	*last_token;

	cur_token = cmd_node->token_list;
	last_token = NULL;
	while (cur_token != NULL)
	{
		flag_quote(cur_token, &flag_dquote, &flag_squote);
		env_value = get_env_value(((t_token *)cur_token->content)->word,
				env_list);
		if (flag_squote == 0 && env_value != NULL)
		{
			cur_token = make_expanded_tokenlist(cur_token, last_token,
					env_value, flag_dquote);
			if (last_token == NULL)
				cmd_node->token_list = cur_token;
			continue ;
		}
		last_token = cur_token;
		cur_token = cur_token->next;
	}
}

// void	edit_env(t_list *cmd_list, t_env_list *env_list)
// {
// 	t_list	*cur_cmd_list;

// 	cur_cmd_list = cmd_list;
// 	while (cur_cmd_list != NULL)
// 	{
// 		expand_env(((t_cmd_node *)cur_cmd_list->content), env_list);
// 		cur_cmd_list = cur_cmd_list->next;
// 	}
// }
