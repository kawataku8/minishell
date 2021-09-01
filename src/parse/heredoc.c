#include "../../include/parse.h"
#include "../../include/cmd.h"

t_list *get_heredoc_delim_token(t_list *cur_token)
{
	while (cur_token != NULL)
	{
		// TODO: error handle
		// >> STR　の間にSTR以外のタイプがある場合　-> NULL返す
		if (((t_token*)cur_token->content)->type == STR)
		{
			((t_token*)cur_token->content)->type = HEREDOC_DELIM;
			break ;
		}
		cur_token = cur_token->next;
	}
	return (cur_token);
}

int open_heredoc_tmp(char *file_path)
{
	char *heredoc_tmp;
	int file_fd;

	// file_pathをmallocして変数に保存
	// heredoc_tmp = ft_strdup(file_path);

	// file_pathからファイルを作る
	file_fd = open("tmp/heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	
	// close(file_fd);
	return (file_fd);
}

int write_heredoc_tmp(int heredoc_fd, char *heredoc_delim)
{
	char *usr_input;
	
	while ((usr_input = readline("> ")) != NULL)
	{
		// Ctrl + Cが押された時の挙動
		// if (signal_handled)
		// {
		// 	signal_handled = 0;
		// 	return  (1);
		// }

		// Ctrl + Dが押された時の挙動
		// if (line == NULL)
		// {
		// 	exit(1);
		// }

		// heredoc_delimが入力された場合
		if (my_strcmp(usr_input, heredoc_delim) == 0)
		{
			return (0);
		}

		// printf("DEBUG:[%s]\n",usr_input);

		write(heredoc_fd, usr_input, ft_strlen(usr_input));
		write(heredoc_fd, &"\n", 1);
		free(usr_input);
		usr_input = NULL;
	}
	return (0);
}

// return: 
// if heredoc is made -> 1
// no heredoc is made -> 0
// error              -> -1
int make_heredoc(t_list *token_list)
{
	t_list *cur_token;
	char *delim_token;
	int heredoc_fd;
	int yes_heredoc;

	yes_heredoc = 0;
	cur_token = token_list;
	while (cur_token)
	{
		if (((t_token*)(cur_token->content))->type != LLDIR)
		{
			cur_token = cur_token->next;
			continue ;
		}

		cur_token = get_heredoc_delim_token(cur_token);
		// if (cur_token == NULL)
			// error handle
		// else
		// delim_token = ft_strdup(((t_token*)(cur_token->content))->word);
		yes_heredoc = 1;
		delim_token = ((t_token*)(cur_token->content))->word;

		heredoc_fd = open_heredoc_tmp("../../tmp/heredoctmp");
		write_heredoc_tmp(heredoc_fd, delim_token);
		close(heredoc_fd);
	}
	return (yes_heredoc);
}

void process_heredoc(t_list *cmd_list)
{
	t_list *cur_cmd;
	t_list *token_list;
	int res;

	cur_cmd = cmd_list;
	while (cur_cmd != NULL)
	{
		// token_listを回してtypeが<<ならheredocの-処理に入る
		token_list = ((t_cmd_node*)cur_cmd->content)->token_list;
		res = make_heredoc(token_list);
		if (res == 1)
			((t_cmd_node*)(cur_cmd->content))->heredoc_flag = 1;
		cur_cmd = cur_cmd->next;
	}

}