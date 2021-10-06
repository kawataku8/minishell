/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:35:21 by takuya            #+#    #+#             */
/*   Updated: 2021/10/03 16:37:29 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

//skip space and retuns next token type
// invalid -> returns 1
// good -> returns 2
int	is_next_sametype(t_list *token_list, int type)
{
	t_list	*cur_token;

	cur_token = token_list;
	while (cur_token != NULL)
	{
		if (((t_token *)cur_token->content)->type == type)
			return (1);
		if (((t_token *)cur_token->content)->type == MYSPACE)
			cur_token = cur_token->next;
		else
			break ;
	}
	return (0);
}

int	is_token_meta(t_list *token)
{
	if (((t_token *)token->content)->type == SCOLON
		|| ((t_token *)token->content)->type == PIPE)
		return (1);
	return (0);
}

// > returns 1, < returns 3, none returns 0
int	is_token_redirect(t_list *token)
{
	if (((t_token *)token->content)->type == RDIR)
		return (RDIR);
	if (((t_token *)token->content)->type == LDIR)
		return (LDIR);
	if (((t_token *)token->content)->type == RRDIR)
		return (RRDIR);
	if (((t_token *)token->content)->type == LLDIR)
		return (LLDIR);
	return (0);
}

// valid return 1, invalid returns 0
// invvalid: <<,<>,<EOF
int	valid_ldir(t_list *token)
{
	t_list	*cur_token;

	cur_token = token->next;
	while (cur_token != NULL)
	{
		if (is_token_redirect(cur_token) || is_token_meta(cur_token))
			return (0);
		if (((t_token *)cur_token->content)->type == MYSPACE)
			cur_token = cur_token->next;
		else
			return (1);
	}
	return (0);
}
