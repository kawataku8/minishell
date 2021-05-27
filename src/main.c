
#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"

int main(int argc, char *argv[])
{
	char *usr_input;
	int size = 100;
	t_list *token_list;


	usr_input = (char*)malloc(sizeof(char)*size);
	fgets(usr_input,size,stdin);

	usr_input[ft_strlen(usr_input)-1] = '\0';
	printf("USER INPUT:%s\n",usr_input);
	
	token_list = make_tokenlist(usr_input);
	print_tokenlist(token_list);

	if(validator(token_list) == 0)
		printf("INVALID\n");
	else
		printf("GOOD\n");

	free(usr_input);
	exit(1);
	return 0;
}