/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:39:10 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 01:39:38 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "commonlib.h"
# include <readline/readline.h>
# include <readline/history.h>

void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	setup_signals(void);

int		check_state(void);

#endif