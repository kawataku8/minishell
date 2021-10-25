/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:41:34 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 23:00:54 by takuya           ###   ########.fr       */
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

void	free_dchar(char **dstr)
{
	int	i;

	if (dstr == NULL)
		return ;
	i = 0;
	while (dstr[i] != NULL)
	{
		free(dstr[i]);
		i++;
	}
	free(dstr);
}
