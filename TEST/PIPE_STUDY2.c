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
		execvp(argv[0], argv);
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

//コマンドが右にパイプ持つ間はwhile回る
//return値：パイプで繋がれた最後のt_command c
t_command *do_pipeline(t_command *c)
{
	int	haspipe = 0;
	int	lastpipe[2] = { -1, -1 };

	while (c)
	{
		c->pid = start_command(c->argv, ispipe(c), haspipe, lastpipe);
		haspipe = ispipe(c);
		if (haspipe)
			c = c->next;
		else
			break ;
	}
	return (c);
}

void run_list(t_command *c)
{
	pid_t pid;

	while (c)
	{
			if (isbuiltin(c) && !ispipe(c))
			{
				/* パイプラインにない組み込みコマンドはシェル（親プロセス）が行う */
				execute_builtin(c->argv);
				c = c->next;
				continue ;
			}
			c = do_pipeline(c);
			wait_pipeline(c->pid);
			c = c->next;
	}
}