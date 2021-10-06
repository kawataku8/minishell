/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:14:09 by takuya            #+#    #+#             */
/*   Updated: 2021/10/03 17:14:25 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/validator.h"

int	is_red_token(t_token *token)
{
	if (RDIR <= token->type && token->type <= LLDIR)
		return (token->type);
	return (0);
}
