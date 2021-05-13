#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../include/cmd.h"
#include "../libft/libft.h"

extern char **environ;

int ispipe(t_cmd_node *cur_cmd_node)
{
	if (cur_cmd_node->next != NULL)
		return 1;
	return 0;
}

void free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_node *cur_cmd_node;
	t_cmd_node *tmp_cmd_node;
	int i;

	cur_cmd_node = cmd_list->head;
	while (cur_cmd_node != NULL)
	{
		tmp_cmd_node = cur_cmd_node->next;
		i = 0;
		while(cur_cmd_node->argv[i] != NULL)
		{
			free(cur_cmd_node->argv[i]);
			i++;
		}
		free(cur_cmd_node->argv);
		free(cur_cmd_node);
		cur_cmd_node = tmp_cmd_node;
	}

}

pid_t	start_command(char *argv[], int ispipe, int haspipe, int lastpipe[2])
{
	pid_t pid;
	int newpipe[2];

	if (ispipe)
		pipe(newpipe);
	pid = fork();
	//子プロセス
	if (pid == 0)
	{
		//左にパイプあり　入力としてパイプ[0],fd0を使う
		if (haspipe)
		{
			close(lastpipe[1]);
			dup2(lastpipe[0], 0);
			close(lastpipe[0]);
		}
		//右にパイプあり　出力をpipe[1],fd1に流す
		if (ispipe)
		{
			close(newpipe[0]);
			dup2(newpipe[1], 1);
			close(newpipe[1]);
		}
		// execvp(argv[0], argv);
		execve(argv[0], argv, environ);
	}
	
	// 上の子プロセスですでに入出力の受け渡しは終了しているので一個前に使ったpipeをclose
	if (haspipe)
	{
		close(lastpipe[0]);
		close(lastpipe[1]);
	}
	if (ispipe)
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
	return (pid);
}

int main(void)
{
	int i = 0;
	int pid, status;
	int	haspipe = 0;
	int	lastpipe[2] = { -1, -1 };


	// redirect out test
	// int out_fd;
	// out_fd = open("outputw", O_CREAT | O_RDWR, S_IRWXU);
	// close(1);
	// dup2(out_fd, 1);
	// close(out_fd);

	//redirect in test
	int in_fd;
	in_fd = open("output", O_RDONLY);
	close(0);
	dup2(in_fd, 0);
	close(in_fd);



	t_cmd_list cmds_list;
	t_cmd_node *cmd_node;

	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	//TODO make_cmd_node("/bin/ls ./")に置き換え
	// cmd_node->argv = ft_split("/bin/ls ./",' ');
	cmd_node->argv = ft_split("/bin/cat",' ');
	cmds_list.head = cmd_node;

	cmds_list.head->next = NULL;

	// cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	// cmd_node->argv = ft_split("/usr/bin/grep .c", ' ');
	// cmds_list.head->next = cmd_node;

	// cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	// cmd_node->argv = ft_split("/usr/bin/wc", ' ');
	// // cmd_node->argv = argv3;
	// cmds_list.head->next->next = cmd_node;

	// cmds_list.head->next->next->next = NULL;
	

	t_cmd_node *cur_cmd_node = cmds_list.head;
	while (cur_cmd_node != NULL)
	{
		cur_cmd_node->pid = start_command(cur_cmd_node->argv, ispipe(cur_cmd_node), haspipe, lastpipe);
		if ((haspipe = ispipe(cur_cmd_node)) == 1)
			cur_cmd_node = cur_cmd_node->next;
		else
			break ;
	}
	
	waitpid(cur_cmd_node->pid,&status,0);

	// pid = wait(&status);
	// printf("DEBUG2:pid id:%d\n",pid);
	// pid = wait(&status);
	// printf("DEBUG2:pid id:%d\n",pid);
	// pid = wait(&status);
	// printf("DEBUG2:pid id:%d\n",pid);

	free_cmd_list(&cmds_list);

	exit(1);
	return 0;
}