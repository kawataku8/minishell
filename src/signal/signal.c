/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:15:03 by takuya            #+#    #+#             */
/*   Updated: 2021/10/13 23:44:20 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

extern volatile sig_atomic_t	g_signal_handled;

void	sigint_handler(int signum)
{
	(void)signum;
	if (g_signal_handled == 0)
	{
		g_signal_handled = 1;
		return ;
	}
}

void	sigquit_handler(int signum)
{
	(void)signum;
	return ;
}

void	setup_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
