#include "../../include/parse.h"
#include "../../include/cmd.h"

extern volatile sig_atomic_t signal_handled;

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
	// file_fd = open("tmp/heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	file_fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	
	// close(file_fd);
	return (file_fd);
}


// returns
// normal, Ctrl+D: 0
// Ctrl+C: 1
int write_heredoc_tmp(int heredoc_fd, char *heredoc_delim)
{
	char *usr_input;
	
	while ((usr_input = readline("> ")) != NULL)
	{
		// Ctrl + Cが押された時の挙動
		if (signal_handled)
		{
			signal_handled = 0;
			free(usr_input);
			return (1) ;
		}

		// heredoc_delimが入力された場合
		if (my_strcmp(usr_input, heredoc_delim) == 0)
		{
			free(usr_input);
			return (0);
		}

		write(heredoc_fd, usr_input, ft_strlen(usr_input));
		write(heredoc_fd, &"\n", 1);
		free(usr_input);
		usr_input = NULL;
	}
	return (0);
}

// returns: 
// if heredoc is made -> 1
// no heredoc is made -> 0
// error              -> -1
int make_heredoc(t_list *cur_cmd, int heredoc_tmp_num)
{
	t_list *cur_token;
	char *delim_word;
	char *num_str;
	char *file_path;
	int heredoc_fd;
	int res;

	// cur_token = token_list;
	cur_token = ((t_cmd_node*)cur_cmd->content)->token_list;
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
		delim_word = ((t_token*)(cur_token->content))->word;

		// "../../tmp/heredoctmp" + heredoc_tmp_num のstrjoin
		// この産業を一つの関数にできる
		num_str = ft_itoa(heredoc_tmp_num);
		file_path = ft_strjoin("tmp/heredoc_tmp", num_str);
		free(num_str);

		((t_cmd_node*)cur_cmd->content)->heredoc_filepath = file_path;
		heredoc_fd = open_heredoc_tmp(file_path);

		res = write_heredoc_tmp(heredoc_fd, delim_word);
		close(heredoc_fd);

	}
	return (res);
}

// cmd_list の大外ループ
// heredoc_tmpの連番をこの関数のループで管理
int process_heredoc(t_list *cmd_list)
{
	t_list *cur_cmd;
	// t_list *token_list;
	int res;
	int heredoc_tmp_num;

	cur_cmd = cmd_list;
	heredoc_tmp_num = 1;
	res = 0;
	while (cur_cmd != NULL)
	{
		// token_listを回してtypeが<<ならheredocの-処理に入る
		// token_list = ((t_cmd_node*)cur_cmd->content)->token_list;

		// res = make_heredoc(token_list, tmp_number);
		res = make_heredoc(cur_cmd, heredoc_tmp_num);

		// heredocを作る途中でエラーになった時のハンドル

		// heredoc 入力中に Ctrl+C押された場合
		if (res == 1)
		{
			// error handle
			break;
		}

		heredoc_tmp_num++;
		cur_cmd = cur_cmd->next;
	}
	return (res);
}