#ifndef DLIST_OPERATIONS_H
# define DLIST_OPERATIONS_H

#include "commonlib.h"

t_env_node *make_node(char *key, char *value);
void insert_after(t_env_list *stack, t_env_node *node, t_env_node *new_node);
void insert_before(t_env_list *stack, t_env_node *node, t_env_node *new_node);
void insert_beginning(t_env_list *stack, t_env_node *new_node);
void insert_end(t_env_list *stack, t_env_node *new_node);
void clear_stack(t_env_list *stack);
void remove_node(t_env_list *stack,t_env_node *node);
void print_env_list(t_env_list *stack);

#endif