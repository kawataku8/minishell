/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:41:34 by takuya            #+#    #+#             */
/*   Updated: 2021/10/17 12:26:14 by takuya           ###   ########.fr       */
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

void	do_cmdlist(t_list *cmd_list, t_env_list *env_list)
{
	signal(SIGQUIT, &sigquit_handler);
	process_cmdlist(cmd_list, env_list);
	signal(SIGQUIT, SIG_IGN);
}

int	is_str_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}