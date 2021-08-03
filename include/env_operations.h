#ifndef ENV_OPERATIONS_H
# define ENV_OPERATIONS_H

#include "commonlib.h"
#include "dlist_operations.h"

int get_chrindex(char *str, char c);
t_env_list *make_envlist(char **envp);

char **make_char_envlist(t_env_list *env_list);
int list_size(t_env_list *env_list);

void mod_envlist_value(char *target_key, char *new_value, t_env_list *env_list);


#endif