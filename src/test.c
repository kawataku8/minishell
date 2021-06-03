#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"
#include "../include/env_operations.h"

int main(int argc, char *argv[], char **envp)
{
	// t_doubly_list *env_list;
	// char *value;
	// int i;
	// int j;
	// env_list = make_envlist(envp);

	// char *word = "yoyo$USER";
	// value = get_env_value(word,env_list);

	// if (value != NULL)
	// {
	// 	printf("[i:%c],[j:%c],[value:%s]\n",word[i],word[j],value);
	// 	free(value);
	// }

	char *s = "$HH";
	char *value = "aloha";
	// char *r = make_new_word(s,value);
	// printf("[%s]\n",r);
	// free(r);
	
	t_list *new_tokenlist = make_new_tokens(s,value);
	while (new_tokenlist != NULL)
	{
		printf("[%s]->",((t_token*)new_tokenlist->content)->word);
		new_tokenlist = new_tokenlist->next;
	}
	printf("\n");

	exit(0);
	return 0;
}