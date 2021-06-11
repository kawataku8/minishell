#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"

int main(void)
{
	char *s = ft_strdup("");
	if (s == NULL)
		printf("YES NULL\n");
	printf("[%s]\n",s);
	free(s);
	return 0;
}