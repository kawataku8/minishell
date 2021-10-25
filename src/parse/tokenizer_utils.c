/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:17:29 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 16:06:35 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/validator.h"

int	specify_tokentype(char c)
{
	if (c == '>')
		return (RDIR);
	else if (c == '<')
		return (LDIR);
	else if (c == ' ')
		return (MYSPACE);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '"')
		return (DQUOTE);
	else if (c == '|')
		return (PIPE);
	else if (c == '&')
		return (AND);
	else if (c == ';')
		return (SCOLON);
	return (0);
}

//return: next squote or EOF index
int	idx_next_squote(char *usr_input, int start)
{
	int	end;

	end = start;
	while (usr_input[end])
	{
		if (usr_input[end] == '\'')
			break ;
		end++;
	}
	end--;
	return (end);
}

void	edit_tokenlist(t_list *token_list)
{
	t_list	*cur_token;
	t_list	*new_list;
	t_token	*new_token;
	int		token_type;

	cur_token = token_list;
	while (cur_token != NULL)
	{
		new_list = NULL;
		token_type = ((t_token *)cur_token->content)->type;
		if (cur_token->next != NULL
			&& (token_type == SQUOTE || token_type == DQUOTE)
			&& (((t_token *)cur_token->next->content)->type == token_type))
		{
			new_token = (t_token *)malloc(sizeof(t_token));
			new_token->word = ft_strdup("\0");
			new_token->type = 0;
			ft_lstadd_back(&new_list, ft_lstnew((void *)new_token));
			new_list->next = cur_token->next;
			cur_token->next = new_list;
		}
		cur_token = cur_token->next;
	}
}
