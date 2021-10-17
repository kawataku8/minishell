/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:53:05 by takuya            #+#    #+#             */
/*   Updated: 2021/10/16 18:15:11 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/cmd.h"
#include "../../include/main.h"

extern volatile sig_atomic_t	g_signal_handled;

// returns
// normal, Ctrl+D: 0
// Ctrl+C: 1
int	write_heredoc_tmp(int heredoc_fd, char *heredoc_delim)
{
	char	*usr_input;

	while (1)
	{
		usr_input = readline("> ");
		if (usr_input == NULL)
			break ;
		if (g_signal_handled)
		{
			g_signal_handled = 0;
			free(usr_input);
			return (1);
		}
		if (my_strcmp(usr_input, heredoc_delim) == 0)
		{
			free(usr_input);
			return (0);
		}
		write(heredoc_fd, usr_input, ft_strlen(usr_input));
		write(heredoc_fd, &"\n", 1);
		free(usr_input);
		usr_input = NULL;
	}
	return (0);
}

char	*make_heredoc_filepath(int heredoc_tmp_num)
{
	char	*num_str;
	char	*file_path;

	num_str = ft_itoa(heredoc_tmp_num);
	file_path = ft_strjoin("tmp/heredoc_tmp", num_str);
	free(num_str);
	return (file_path);
}

int	open_write_herecdoc(char *file_path, char *delim_word)
{
	int	heredoc_fd;
	int	res;

	heredoc_fd = open_heredoc_tmp(file_path);
	res = write_heredoc_tmp(heredoc_fd, delim_word);
	close(heredoc_fd);
	return (res);
}

// returns: 
// if heredoc is made -> 1
// no heredoc is made -> 0
// error              -> -1
int	make_heredoc(t_list *cur_cmd, int heredoc_tmp_num)
{
	t_list	*cur_token;
	char	*delim_word;
	char	*file_path;
	int		res;

	res = 0;
	cur_token = ((t_cmd_node *)cur_cmd->content)->token_list;
	while (cur_token)
	{
		if (((t_token *)(cur_token->content))->type != LLDIR)
		{
			cur_token = cur_token->next;
			continue ;
		}
		cur_token = get_heredoc_delim_token(cur_token);
		if (cur_token == NULL)
			return (1);
		delim_word = ((t_token *)(cur_token->content))->word;
		file_path = make_heredoc_filepath(heredoc_tmp_num);
		((t_cmd_node *)cur_cmd->content)->heredoc_filepath = file_path;
		res = open_write_herecdoc(file_path, delim_word);
		if (res == 1)
			break ;
	}
	return (res);
}

int	process_heredoc(t_list *cmd_list)
{
	t_list	*cur_cmd;
	int		res;
	int		heredoc_tmp_num;

	cur_cmd = cmd_list;
	heredoc_tmp_num = 1;
	res = 0;
	while (cur_cmd != NULL)
	{
		res = make_heredoc(cur_cmd, heredoc_tmp_num);
		if (res == 1)
			break ;
		heredoc_tmp_num++;
		cur_cmd = cur_cmd->next;
	}
	return (res);
}
