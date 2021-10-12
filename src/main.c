/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:02:04 by takuya            #+#    #+#             */
/*   Updated: 2021/10/12 21:41:08 by takuya           ###   ########.fr       */
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

volatile sig_atomic_t	g_signal_handled = 0;

void	del_token(void *content)
{
	free(((t_token *)content)->word);
	free((t_token *)content);
}

// free_splitstr(((t_cmd_node*)cur_cmdlist->content)->argv);
void	free_cmdlist(t_list **cmd_list)
{
	t_list	*cur_cmdlist;
	t_list	*next_cmdlist;

	cur_cmdlist = *cmd_list;
	while (cur_cmdlist != NULL)
	{
		next_cmdlist = cur_cmdlist->next;
		if (((t_cmd_node *)cur_cmdlist->content)->heredoc_filepath != NULL)
		{
			unlink(((t_cmd_node *)cur_cmdlist->content)->heredoc_filepath);
			free(((t_cmd_node *)cur_cmdlist->content)->heredoc_filepath);
		}
		ft_lstclear(&((t_cmd_node *)cur_cmdlist->content)->token_list,
			&del_token);
		cur_cmdlist = next_cmdlist;
	}
}

int	manage_usr_input(char *usr_input, t_env_list *env_list)
{
	if (usr_input == NULL)
		return (1);
	if (usr_input[0] == 0 || g_signal_handled)
	{
		if (g_signal_handled)
		{
			g_signal_handled = 0;
			mod_envlist_value("?", ft_itoa(1), env_list);
		}
		free(usr_input);
		return (2);
	}
	my_add_history(usr_input);
	return (0);
}

t_list	*pre_process(char **usr_input, t_env_list *env_list, int *bc_flag)
{
	int		res;
	t_list	*token_list;
	t_list	*cmd_list;

	*usr_input = trim_usr_input(*usr_input);
	res = manage_usr_input(*usr_input, env_list);
	*bc_flag = 1;
	if (res == 1)
		return (NULL);
	*bc_flag = 2;
	if (res == 2)
		return (NULL);
	token_list = manage_tokenlist(*usr_input);
	if (token_list == NULL)
	{
		mod_envlist_value("?", ft_itoa(258), env_list);
		return (NULL);
	}
	cmd_list = manage_cmdlist(token_list, env_list);
	if (cmd_list == NULL)
	{
		return (NULL);
	}
	*bc_flag = 0;
	return (cmd_list);
}

// readline中に
// Ctrl + Cが押された時
// 何も入力されずreturnキーだけ押された時
int	main(int argc, char *argv[], char **envp)
{
	char		*usr_input;
	t_env_list	*env_list;
	t_list		*cmd_list;
	int			bc_flag;

	setup_signals();
	env_list = make_envlist(envp);
	rl_event_hook = check_state;
	while (1)
	{
		usr_input = readline("minishell$ ");
		cmd_list = pre_process(&usr_input, env_list, &bc_flag);
		if (bc_flag == 1)
			break ;
		else if (bc_flag == 2)
			continue ;
		do_cmdlist(cmd_list, env_list);
		free(usr_input);
		usr_input = NULL;
		free_cmdlist(&cmd_list);
	}
	exit(0);
	return (0);
}
