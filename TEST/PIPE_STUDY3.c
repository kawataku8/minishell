#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

extern char **environ;

int ispipe(int i)
{
	if (i < 1)
		return 1;
	return 0;
}

pid_t start_command(char *argv[], int ispipe, int haspipe, int lastpipe[2], int i)
{
	int file_fd;
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

		if (i == 0)
		{
			file_fd = open("out101", O_CREAT | O_RDWR, S_IRWXU);
			close(1);
			dup2(file_fd, 1);
			close(file_fd);
		}
		if (i == 1)
		{
			file_fd = open("out102", O_CREAT | O_RDWR, S_IRWXU);
			close(1);
			dup2(file_fd, 1);
			close(file_fd);
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
	int haspipe = 0;
	int lastpipe[2] = {-1, -1};

	char **argv;
	char *argv1[] = {"/bin/ls", "./", NULL};
	char *argv2[] = {"/bin/ls", "./", NULL};
	// char *argv2[] = {"/usr/bin/grep", "SIG", NULL};
	char *argv3[] = {"/usr/bin/wc", NULL};

	while (i < 2)
	{
		if (i == 0)
		{
			argv = argv1;
		}
		else if (i == 1)
		{
			argv = argv2;
		}
		// else
		// 	argv = argv3;

		pid = start_command(argv, ispipe(i), haspipe, lastpipe, i);
		haspipe = ispipe(i);
		if (haspipe)
		{
			i++;
		}
		else
		{
			// printf("DEBUG: i is %d\n",i);
			break;
		}
	}

	waitpid(pid, &status, 0);
	wait(&status);
	// wait(&status);
	// exit(1);
	return 0;
}