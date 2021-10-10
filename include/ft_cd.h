/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:20:28 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 01:20:31 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

# include "commonlib.h"

char	*set_oldpwd_path(t_env_list *list);
void	set_pwd_and_oldpwd(t_env_list *list, char *path);
char	*set_path(char **argv, int argc, t_env_list *list);
int		is_valid_arg(int argc, t_env_list *list);
int		chdir_error_message(char *path);
int		ft_cd(int argc, char **argv, t_env_list *list);

#endif