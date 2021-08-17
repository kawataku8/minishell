#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void print_str(char *str)
{
	printf("DEBUG:%s\n",str);
}

int main(void)
{
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
	
	return 0;
}