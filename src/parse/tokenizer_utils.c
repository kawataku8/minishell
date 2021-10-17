/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:17:29 by takuya            #+#    #+#             */
/*   Updated: 2021/10/16 22:15:11 by takuya           ###   ########.fr       */
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
