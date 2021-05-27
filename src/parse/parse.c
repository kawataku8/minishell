/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:29:40 by takuya            #+#    #+#             */
/*   Updated: 2021/05/17 22:55:24 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"


//usr_inputをパース,validateして構造体processを返す
t_process *parse(char *usr_input)
{	
	char **split_usrinput;
	t_list *tokens;
	t_process *process;

	validate_usrinput(usr_input);

	//特殊文字は一文字づつ、スペースで区切られたwordでtokenise
	process = setup_process(split_usrinput);
	
	
	

	return ()
}