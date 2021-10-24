#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

	char *str;

	str = strdup(NULL);
	if(str == NULL)
		return 1;
	// printf("%s\n",str);
	// free(str);
	return 0;
}