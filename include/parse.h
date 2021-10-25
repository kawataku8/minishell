/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:33:15 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 15:55:25 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "commonlib.h"
# include <readline/readline.h>
# include <readline/history.h>

int			specify_tokentype(char c);
int			idx_next_squote(char *usr_input, int start);
int			idx_next_dquote(char *usr_input, int start);
int			idx_with_red(char *usr_input, int start);
int			idx_next_delim(char *usr_input, int start);
t_token		*make_token(char *usr_input, int *i, int in_squote, int in_dquote);
t_list		*make_tokenlist(char *usr_input);
void		print_tokenlist(t_list *token_list);
void		print_cmdlist(t_list *cmd_list);
t_cmd_node	*new_cmdnode(void);
t_list		*make_cmdlist(t_list *token_list);

int			is_num_str(char *str);
void		set_redirect_fd(t_list *token_list);
void		close_red_filefds(t_list *token_list);

int			*dup_original_fds(void);
void		reset_fds_orig(int *original_fds);

int			is_red_token(t_token *token);
t_list		*get_red_filepath_token(t_list *cur_token);
int			connect_redirect(int red_type, int red_fd, char *red_filepath);
// void set_red_fd(int *red_fd, int red_type);
int			set_red_fd(t_list *last_token, int red_type);
void		parse_redirect(t_cmd_node *cmd_node);

t_list		*get_heredoc_delim_token(t_list *cur_token);
int			open_heredoc_tmp(char *file_path);
int			write_heredoc_tmp(int heredoc_fd, char *heredoc_delim);
int			make_heredoc(t_list *cur_cmd, int heredoc_tmp_num);
int			process_heredoc(t_list *cmd_list);

void		edit_tokenlist(t_list *token_list);

#endif