/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:15:03 by takuya            #+#    #+#             */
/*   Updated: 2021/10/03 16:54:01 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

extern volatile sig_atomic_t	g_signal_handled;

void	sigint_handler(int signum)
{
	if (g_signal_handled == 0)
	{
		g_signal_handled = 1;
		return ;
	}
}

void	sigquit_handler(int signum)
{
	return ;
}

void	setup_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
