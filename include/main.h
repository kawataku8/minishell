/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:21:12 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 01:21:27 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <readline/readline.h>
# include <readline/history.h>

void	del_token(void *content);
void	free_cmdlist(t_list **cmd_list);
int		manage_usr_input(char *usr_input, t_env_list *env_list);
t_list	*pre_process(char **usr_input, t_env_list *env_list, int *bc_flag);

char	*trim_usr_input(char *usr_input);
t_list	*manage_tokenlist(char *usr_input);
t_list	*manage_cmdlist(t_list *token_list, t_env_list *env_list);
void	my_add_history(char *usr_input);

#endif