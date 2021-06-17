#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	int file_fd = open("out201", O_RDONLY);
	printf("RESULT:%d\n",file_fd);
	
	close(file_fd);
	return 0;
}