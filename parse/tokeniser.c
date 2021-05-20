/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 09:47:43 by takuya            #+#    #+#             */
/*   Updated: 2021/05/19 21:20:13 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"


// DEBUG func
void print_cmdlist(t_list *cmd_list)
{
	t_list *cur_cumdnode = cmd_list;

	while(cur_cumdnode != NULL)
	{
		int i = 0;
		while(((t_cmd_node*)cur_cumdnode->content)->argv[i] != NULL)
			printf("DEBUG:3:%s,",((t_cmd_node*)cur_cumdnode->content)->argv[i++]);
		cur_cumdnode = cur_cumdnode->next;
	}
	printf("\n\n");
	
}

// DEBUG func
void print_processlist(t_list *process_list)
{
	t_list *cur_processnode = process_list;
	t_list *cur_cmdnode;
	while(cur_processnode != NULL)
	{
		cur_cmdnode = (((t_process*)cur_processnode->content)->cmd_listhead);
		while (cur_cmdnode != NULL)
		{
			int i = 0;
			while(((t_cmd_node*)cur_cmdnode->content)->argv[i] != NULL)
				printf("%s,",((t_cmd_node*)cur_cmdnode->content)->argv[i++]);
			printf("\n");
			cur_cmdnode = cur_cmdnode->next;
		}
		printf("\n\n");
		cur_processnode = cur_processnode->next;
	}
	
}

void free_splitwords(char **words)
{
	int i;

	i = 0;
	while(words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
	words = NULL;
}

void del_cmdnode(void *content)
{
	free_splitwords(((t_cmd_node*)content)->argv);
	free((t_cmd_node*)content);
}

void clear_processlist(t_list **process_list, void (*del)(void *))
{
	t_list *next_lst;
	t_list *lst_temp;

	if (process_list && del)
	{
		lst_temp = *process_list;
		while (lst_temp)
		{
			next_lst = lst_temp->next;
			// free(((t_process*)lst_temp->content)->red_in_filepath);
			// free(((t_process*)lst_temp->content)->red_out_filepath);
			// free(((t_process*)lst_temp->content)->red_err_filepath);
			ft_lstclear( &(((t_process*)lst_temp->content)->cmd_listhead),del);
			free((t_process*)lst_temp->content);
			free(lst_temp);
			lst_temp = next_lst;
		}
		*process_list = NULL;
	}

}

t_list *setup_process(char *usr_input)
{
	t_list *process_list = NULL;
	t_list *cmd_list = NULL;
	t_process *process_node;
	t_cmd_node *cmd_node;
	char **split_bysemi;
	char **split_bypipe;
	int i;
	int j;

	// echo hello|wc; ls|grep .c|wc;env
	//"echo hello|wc", "ls|grep .c|wc", "env"
	split_bysemi = ft_split(usr_input,';');
	
	i = 0;
	//t_list processのループでもある ； ごとにprocessは増える
	while(split_bysemi[i] != NULL)
	{
		//"echo hello|wc"
		//"echo hello", "wc"
		// printf("DEBUG:%s\n",split_bysemi[i]);
		split_bypipe = ft_split(split_bysemi[i],'|');

		//"echo hello"
		//"echo","hello"
		//ここでスプリットしたものがcmd_nodeのargvに入る
		j = 0;
		cmd_node = NULL;
		cmd_list = NULL;
		while(split_bypipe[j] != NULL)
		{
			cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
			cmd_node->argv = ft_split(split_bypipe[j],' ');
			ft_lstadd_back(&cmd_list,ft_lstnew((void*)cmd_node));
			j++;
		}
		process_node = (t_process*)malloc(sizeof(t_process));
		process_node->cmd_listhead = cmd_list;
		ft_lstadd_back(&process_list,ft_lstnew((void*)process_node));

		free_splitwords(split_bypipe);
		i++;
	}

	free_splitwords(split_bysemi);

	return (process_list);
}





int main(int argc, char *argv[])
{
	int i = 0;

	while(i < argc)
	{
		printf("%s\n",argv[i]);
		i++;
	}



	// t_list *process_list;

	// process_list =  setup_process("ls |grep .c| wc; echo hello; env ;echo \"hello\">yoyo");
	// // printf(((t_process*)process_list->content)->cmd_listhead->content )
	// print_processlist(process_list);
	// clear_processlist(&process_list,&del_cmdnode);

	return 0;
}