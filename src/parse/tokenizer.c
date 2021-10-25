/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:08:34 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 23:03:18 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/validator.h"
#include "../../include/main.h"

//return: next dquote or EOF index
int	idx_next_dquote(char *usr_input, int start)
{
	int	end;

	end = start;
	while (usr_input[end])
	{
		if (usr_input[end] == '\\')
		{
			if (usr_input[end + 1] && (usr_input[end + 1] == '\\'
					|| usr_input[end + 1] == '"'))
			{
				end += 2;
				continue ;
			}
		}
		if (usr_input[end] == '"')
			break ;
		end++;
	}
	end--;
	return (end);
}

int	idx_with_red(char *usr_input, int start)
{
	int	end;
	int	type;

	type = specify_tokentype(usr_input[start]);
	end = start;
	if (type == RDIR && usr_input[end + 1]
		&& specify_tokentype(usr_input[end + 1]) == RDIR)
		end++;
	if (type == LDIR && usr_input[end + 1]
		&& specify_tokentype(usr_input[end + 1]) == LDIR)
		end++;
	return (end);
}

//return:next meta oor EOF index
int	idx_next_delim(char *usr_input, int start)
{
	int	end;

	end = start;
	while (usr_input[end])
	{
		if (specify_tokentype(usr_input[end]) > 0)
			break ;
		end++;
	}
	if (start != end)
		end--;
	return (end);
}

t_token	*make_token(char *usr_input, int *i, int in_squote, int in_dquote)
{
	t_token		*new_token;
	int			type;
	int			end;

	type = specify_tokentype(usr_input[*i]);
	if (in_squote && type != SQUOTE)
		end = idx_next_squote(usr_input, *i);
	else if (in_dquote && type != DQUOTE)
		end = idx_next_dquote(usr_input, *i);
	else if (type == RDIR || type == LDIR)
		end = idx_with_red(usr_input, *i);
	else
		end = idx_next_delim(usr_input, *i);
	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->word = ft_substr(usr_input, *i, end - (*i) + 1);
	if (type == RDIR && ft_strlen(new_token->word) == 2)
		new_token->type = RRDIR;
	else if (type == LDIR && ft_strlen(new_token->word) == 2)
		new_token->type = LLDIR;
	else if (type == 6 && (in_squote || in_dquote))
		new_token->type = 0;
	else
		new_token->type = type;
	*i = end;
	return (new_token);
}

t_list	*make_tokenlist(char *usr_input)
{
	t_list	*token_list;
	t_token	*new_token;
	int		i;
	int		in_dquote;
	int		in_squote;

	token_list = NULL;
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (usr_input[i])
	{	
		if (!(in_dquote) && (specify_tokentype(usr_input[i]) == SQUOTE))
			in_squote ^= 1;
		else if (!(in_squote) && (specify_tokentype(usr_input[i]) == DQUOTE))
			in_dquote ^= 1;
		new_token = make_token(usr_input, &i, in_squote, in_dquote);
		ft_lstadd_back(&token_list, ft_lstnew((void *)new_token));
		i++;
	}
	set_redirect_fd(token_list);
	return (token_list);
}

// void print_tokenlist(t_list *token_list)
// {
// 	t_list *cur_node = token_list;
// 	while(cur_node != NULL)
// 	{
// 		printf("[%d]:[%s], ",((t_token*)cur_node->content)->type,
// ((t_token*)cur_node->content)->word);
// 		cur_node = cur_node->next;
// 	}
// 	printf("\n");
// }
