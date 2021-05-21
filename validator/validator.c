/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:59:35 by takuya            #+#    #+#             */
/*   Updated: 2021/05/21 23:24:22 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/validator.h"


//skip space and retuns next token type
int is_next_sametype(t_list *token_list, int type)
{
	t_list *cur_token;

	cur_token = token_list;
	while (cur_token != NULL)
	{
		if (((t_token*)cur_token->content)->type == type)
			return (1);
		if (((t_token*)cur_token->content)->type == SPACE)
			cur_token = cur_token->next;
		else
			break ;
	}
	return (0);
}

int is_token_meta(t_list *token)
{
	if (((t_token*)token->content)->type == SCOLON 
	|| ((t_token*)token->content)->type == PIPE)
		return (1);
	return (0);
}

// > returns 1, < returns 3, none returns 0
int is_token_redirect(t_list *token)
{
	if(((t_token*)token->content)->type == RDIR)
		return (RDIR);
	if(((t_token*)token->content)->type == LDIR)
		return (LDIR);
	return (0);
}

// valid return 1, invalid returns 0
int valid_meta_syntax(t_list *token)
{
	if (is_token_meta(token))
	{
		if(token->next != NULL)
		{
			if(is_next_sametype(token->next, SCOLON) 
			|| is_next_sametype(token->next, PIPE))
				return 0;
		}
	}
	return (1);
}

// valid return 1, invalid returns 0
// invvalid: <<,<>,<EOF
int valid_LDIR(t_list *token)
{
	t_list *cur_token;
	
	cur_token = token->next;
	while(cur_token != NULL)
	{
		if (is_token_redirect(cur_token) || is_token_meta(cur_token))
			return (0);
		if (((t_token*)cur_token->content)->type == SPACE)
			cur_token = cur_token->next;
		else
			return (1);
	}
	return (0);
}

// valid return 1, invalid returns 0
// invvalid: >>>,>> >,> >>,> >,>EOF,>>EOF
int valid_RDIR(t_list *token)
{
	t_list *cur_token;
	int flag_space;
	int times_RDIR;
	
	cur_token = token->next;
	flag_space = 0;
	times_RDIR = 1;
	while(cur_token != NULL)
	{
		if (is_token_redirect(cur_token) == LDIR || is_token_meta(cur_token))
			return (0);
		else if (is_token_redirect(cur_token) == RDIR)
		{
			times_RDIR++;
			if (flag_space || times_RDIR > 2)
				return (0);
			cur_token = cur_token->next;
			continue;
		}
		else if (((t_token*)cur_token->content)->type != SPACE)
			return (1);
		flag_space++;
		cur_token = cur_token->next;
	}
	return (0);
}

// valid return 1, invalid returns 0
int valid_redirect_syntax(t_list *token)
{
	if (is_token_redirect(token) == LDIR && valid_LDIR(token) == 0)
		return (0);
	if (is_token_redirect(token) == RDIR && valid_RDIR(token) == 0)
		return (0);
	return (1);
}

void swich_quote_flag(t_list *cur_token,int *flag_squote,int *flag_dquote)
{
	if(((t_token*)cur_token->content)->type == SQUOTE)	
		*flag_squote ^= 1;
	if(((t_token*)cur_token->content)->type == DQUOTE)
		*flag_dquote ^= 1;
}

// valid returns 1, invalid returns 0
int validator(t_list *token_list)
{
	t_list *cur_token;
	int flag_squote;
	int	flag_dquote;

	flag_squote = 0;
	flag_dquote = 0;
	cur_token = token_list;
	if (is_token_meta(cur_token))
		return (0);
	while(cur_token != NULL)
	{
		printf("DEBUG:%s\n",((t_token*)cur_token->content)->word);
		swich_quote_flag(cur_token, &flag_squote, &flag_dquote);
		if(!(valid_meta_syntax(cur_token)))
		{
			printf("DEBUG:meta syntax error\n");
			return (0);
		}
		if(!(valid_redirect_syntax(cur_token)))
		{
			printf("DEBUG:redirect syntax error\n");
			return (0);
		}
		cur_token = cur_token->next;
	}
	if(flag_squote || flag_dquote)
		return (0);
	return (1);
}