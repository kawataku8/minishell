 
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[],char **envp)
{

	while(*envp != NULL)
	{
		printf("%s\n",*envp);
		envp++;
	}
	
	return 0;
}