#include "../../include/env_operations.h"

int list_size(t_env_list *env_list)
{
	int n;
	t_env_node *cur_envnode;

	cur_envnode = env_list->head;
	n = 0;
	while(cur_envnode != NULL)
	{
		++n;
		cur_envnode = cur_envnode->next;
	}
	return (n);
}

char **make_char_envlist(t_env_list *env_list)
{
	char *tmp;
	char **char_envlist;
	int n;
	t_env_node *cur_envnode;

	char_envlist = (char**)malloc((sizeof(char*) * list_size(env_list)) + 1);
	cur_envnode = env_list->head;
	n = 0;
	while(cur_envnode != NULL)
	{
		tmp = ft_strjoin(cur_envnode->key,"=");
		char_envlist[n++] = ft_strjoin(tmp,cur_envnode->value);
		free(tmp);
		cur_envnode = cur_envnode->next;
	}
	char_envlist[n] = NULL;

	return (char_envlist);
}