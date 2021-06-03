#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"

int main(void)
{
	char *s1 = "heyo";
	char *s2 = "heyo";
	printf("%s,%s\n",s1,s2);
	if (my_strcmp(s1,s2) == 0)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}