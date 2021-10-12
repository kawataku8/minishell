/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:07:23 by takuya            #+#    #+#             */
/*   Updated: 2021/10/12 21:40:19 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"
#include "../include/env_operations.h"
#include "../include/setup.h"
#include "../include/main.h"
#include "../include/signal.h"

extern volatile sig_atomic_t	g_signal_handled;

char	*trim_usr_input(char *usr_input)
{
	char	*tmp;

	tmp = ft_strtrim(usr_input, "	 ");
	free(usr_input);
	return (tmp);
}

t_list	*manage_tokenlist(char *usr_input)
{
	t_list	*token_list;

	token_list = make_tokenlist(usr_input);
	if (validator(token_list) == 0)
	{
		my_write_err_msg(2, "minishell: syntax error", -1);
		free(usr_input);
		usr_input = NULL;
		return (NULL);
	}
	return (token_list);
}

t_list	*manage_cmdlist(t_list *token_list, t_env_list *env_list)
{
	t_list	*cmd_list;
	int		res;

	cmd_list = make_cmdlist(token_list);
	setup_op(cmd_list);
	res = process_heredoc(cmd_list);
	if (res == 1)
	{
		mod_envlist_value("?", ft_itoa(res), env_list);
		free_cmdlist(&cmd_list);
		return (NULL);
	}
	return (cmd_list);
}

void	my_add_history(char *usr_input)
{
	if (ft_strlen(usr_input) > 0)
		add_history(usr_input);
}

void	my_write_err_msg(int fd, char *str, int err_num)
{
	char	*err_str;

	write(fd, str, ft_strlen(str));
	if (err_num > 0)
	{
		err_str = strerror(err_num);
		write(fd, err_str, ft_strlen(err_str));
	}
	write(fd, &"\n", 1);
}
