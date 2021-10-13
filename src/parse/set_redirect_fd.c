/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:29:31 by takuya            #+#    #+#             */
/*   Updated: 2021/10/13 23:38:52 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/validator.h"

int	is_num_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	set_redirect_fd(t_list *token_list)
{
	t_list	*cur_token;
	t_list	*prev_token;

	prev_token = token_list;
	if (prev_token == NULL)
		return ;
	cur_token = token_list->next;
	while (cur_token != NULL)
	{
		if (is_token_redirect(cur_token))
		{
			if (is_num_str(((t_token *)prev_token->content)->word))
				((t_token *)prev_token->content)->type = REDFD;
		}
		prev_token = cur_token;
		cur_token = cur_token->next;
	}
}
