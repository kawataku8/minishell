#ifndef CMD_H
# define CMD_H


//一つのコマンドを表す構造体
//• argc > 1 の場合は
//next != NULL 右にpipe | を持つ
//next == NULL pipe cmdsの最後のコマンド
typedef struct	s_cmd_node
{
	struct s_cmd_node	*next;
	pid_t 				pid;
	//numbers of argv
	// int					argc;
	//["grep","s"]
	char				**argv;
	// //右にpipe | を持つかどうか
	// int					op;
}				t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node *head;
}				t_cmd_list;

#endif
