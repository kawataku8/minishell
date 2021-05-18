#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *str = "hello\n";

	write(1,str,strlen(str));
	return 0;
}