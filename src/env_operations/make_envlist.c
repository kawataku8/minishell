#include "../include/env_operations.h"

int get_chrindex(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

// TEST=hello
t_doubly_list *make_envlist(char **envp)
{
	t_doubly_list *env_list;
	t_env_node *new_envnode;
	char *key;
	char *value;
	int eql_idx;
	
	env_list = (t_doubly_list*)malloc(sizeof(t_doubly_list));
	env_list->head = NULL;
	env_list->tail = NULL;
	while(*envp != NULL)
	{
		eql_idx = get_chrindex(*envp, '=');

		key = ft_substr(*envp,0,eql_idx);
		value = ft_substr(*envp,eql_idx+1,ft_strlen(*envp)-eql_idx+1);
		new_envnode = make_node(key,value);
		insert_end(env_list,new_envnode);
		
		envp++;
	}

	return (env_list);
}

// int main(int argc, char *argv[],char **envp)
// {
// 	t_doubly_list *env_list;

// 	env_list = make_envlist(envp);
// 	print_doubly_list(env_list);
// 	clear_stack(env_list);

// 	exit(1);
// 	return 0;
// }