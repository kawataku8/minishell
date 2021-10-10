/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 00:03:41 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 01:41:17 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "commonlib.h"

int		is_next_sametype(t_list *token_list, int type);
int		is_token_meta(t_list *token);
int		is_token_redirect(t_list *token);
int		valid_meta_syntax(t_list *token);
int		valid_ldir(t_list *token);
int		valid_redirect(t_list *token);
int		valid_redirect_syntax(t_list *token);
void	swich_quote_flag(t_list *cur_token, int *flag_squote, int *flag_dquote);
int		validator(t_list *token_list);

#endif
