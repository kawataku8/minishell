#ifndef ENV_OPERATIONS_H
# define ENV_OPERATIONS_H

#include "commonlib.h"
#include "dlist_operations.h"

int get_chrindex(char *str, char c);
t_env_list *make_envlist(char **envp);


#endif