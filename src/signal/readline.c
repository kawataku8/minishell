/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:21 by takuya            #+#    #+#             */
/*   Updated: 2021/10/02 13:14:20 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

extern volatile sig_atomic_t signal_handled;

int	check_state(void)
{
	if (signal_handled)
	{
		rl_delete_text(0, rl_end);
		rl_done = 1;
	}
	return (0);
}
