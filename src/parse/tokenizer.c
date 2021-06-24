/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:08:34 by takuya            #+#    #+#             */
/*   Updated: 2021/06/24 15:57:44 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/validator.h"

int specify_tokentype(char c)
{
	if(c == '>')
		return (RDIR);
	else if(c == '<')
		return (LDIR);
	else if(c == ' ')
		return (MYSPACE);
	else if(c == '\'')
		return (SQUOTE);
	else if(c == '"')
		return (DQUOTE);
	else if(c == '|')
		return (PIPE);
	else if(c == '&')
		return (AND);
	else if(c == ';')
		return (SCOLON);
	// else if(c == '\\')
	// 	return (ESC);
	return (0);
}

//return: 次の シングルオートまたはEOF のindex
int idx_next_squote(char *usr_input, int start)
{
	int end;

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

//return: startから次の ダブルクオートまたはEOF のindex
int idx_next_dquote(char *usr_input, int start)
{
	int end;

	end = start;
	while (usr_input[end])
	{
		if (usr_input[end] == '\\')
		{
			if (usr_input[end+1] && (usr_input[end+1] == '\\' || usr_input[end+1] == '"'))
			{
				end += 2;
				continue;
			}
		}
		if (usr_input[end] == '"')
			break ;
		end++;
	}
	end--;
	return (end);
}

int idx_with_red(char *usr_input, int start)
{
	int end;
	int type;

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

//return:次の 特殊文字またはEOF のindex
// TODO: rdir,ldirの進めは別関数
int idx_next_delim(char *usr_input, int start)
{
	int end;

	end = start;
	while (usr_input[end])
	{
		if (specify_tokentype(usr_input[end]) > 0)
			break ;
		end++;
	}
	// abc; なら endはインデックス 2 にしたいので　end--
	// start == end の場合はそのまま
	if (start != end)
		end--;
	return (end);
}

t_token *make_token(char *usr_input, int *i,int in_squote, int in_dquote)
{
	t_token *new_token;
	int type;
	int start;
	int end;

	type = specify_tokentype(usr_input[*i]);
	if(in_squote && type != SQUOTE)
		end = idx_next_squote(usr_input,*i);
	else if(in_dquote && type != DQUOTE)
		end = idx_next_dquote(usr_input,*i);
	else if(type == RDIR || type == LDIR)
		end = idx_with_red(usr_input,*i);
	else
		end = idx_next_delim(usr_input,*i);

	new_token = (t_token*)malloc(sizeof(t_token));
	new_token->word = ft_substr(usr_input,*i,end-(*i)+1);
	if (type == RDIR && ft_strlen(new_token->word) == 2)
		new_token->type = RRDIR;
	else if (type == LDIR && ft_strlen(new_token->word) == 2)
		new_token->type = LLDIR;
	else
		new_token->type = type;
	*i = end;
	return (new_token);
}

// ここでvalidationはしない
// 特殊文字で区切ってtokenizeのみ
t_list *make_tokenlist(char *usr_input)
{
	t_list *token_list;
	t_token *new_token;
	int i;
	int in_dquote;
	int in_squote;

	token_list = NULL;
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while(usr_input[i])
	{	
		if(!(in_dquote) && (specify_tokentype(usr_input[i]) == SQUOTE))
			in_squote ^= 1;
		else if(!(in_squote) && (specify_tokentype(usr_input[i]) == DQUOTE))
			in_dquote ^= 1;
		new_token = make_token(usr_input,&i,in_squote, in_dquote);
		ft_lstadd_back(&token_list,ft_lstnew((void*)new_token));
		i++;
	}
	set_redirect_fd(token_list);
	return (token_list);
}


void print_tokenlist(t_list *token_list)
{
	t_list *cur_node = token_list;
	while(cur_node != NULL)
	{
		printf("type:[%d]\n",((t_token*)cur_node->content)->type);
		printf("word:[%s]\n",((t_token*)cur_node->content)->word);
		printf("---------------------------\n");
		cur_node = cur_node->next;
	}
}