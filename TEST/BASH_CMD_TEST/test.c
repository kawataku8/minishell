#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{

	char *s = "MORNING\n";
	write(3,s, strlen(s));
	return 0;
}
