#include <stdio.h>

void print_str(char *str)
{
	printf("DEBUG:%s\n",str);
}

int main(void)
{
	char *str = "/hello";
	printf("D:%d\n",str[0]);
	return 0;
}