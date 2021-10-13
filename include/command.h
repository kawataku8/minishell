/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:07:38 by takuya            #+#    #+#             */
/*   Updated: 2021/10/13 23:46:29 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "commonlib.h"
# include "exit_status.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h> 
# include <errno.h> 

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define SUCCESS 1
# define ERROR -1

# define FALSE 0
# define TRUE 1

void			put_string_fd(char *str, int fd);
void			put_endl(int fd);
t_env_node		*make_env_node(char *key, char *value);
void			insert_end(t_env_list *list, t_env_node *new_node);
void			merge_sort(t_env_node **head);
t_env_node		*serch_nodes(t_env_list *list, char *keybuf);
int				ft_cd(int argc, char **argv, t_env_list *list);
int				ft_echo(char **argv);
int				ft_env(t_env_list *list);
int				ft_pa_exit(char **argv, int argc);
int				ft_ch_exit(char **argv, int argc);
int				ft_export(char **argv, t_env_list *list);
int				ft_pwd(void);
int				ft_unset(char **argv, t_env_list *list);
int				malloc_error(void);
int				is_valid_env_key(char *key);
void			put_space(int fd);
void			export_env_list(t_env_list *list);
char			*set_oldpwd_path(t_env_list *list);
void			set_pwd_and_oldpwd(t_env_list *list);
void			clear_env_list(t_env_list *stack);
void			remove_env_node(t_env_list *stack, t_env_node *node);
char			**make_env_arr(t_env_list *list);

#endif