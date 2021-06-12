#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *line;
	
	line = readline("INPUT: ");
	printf("[%s]\n",line);

	char *new_s;
	char *set = "	 ";
	new_s = ft_strtrim(line,set);
	printf("[%s]\n",new_s);


	free(line);
	free(new_s);
	
	return 0;
}