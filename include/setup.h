/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:37:41 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 22:23:01 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "commonlib.h"
# include "setup.h"

void	setup_op(t_list *cmd_list);
int		count_strtoken(t_list *token);
void	setup_argv_argc(t_cmd_node *cmd_node);
int		is_next_delim_space(t_list *cur_token);

#endif