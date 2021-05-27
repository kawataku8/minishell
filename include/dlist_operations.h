#ifndef DLIST_OPERATIONS_H
# define DLIST_OPERATIONS_H


#include "commonlib.h"

t_env_node *make_node(char *key, char *value);
void insert_after(t_doubly_list *stack, t_env_node *node, t_env_node *new_node);
void insert_before(t_doubly_list *stack, t_env_node *node, t_env_node *new_node);
void insert_beginning(t_doubly_list *stack, t_env_node *new_node);
void insert_end(t_doubly_list *stack, t_env_node *new_node);
void clear_stack(t_doubly_list *stack);
void remove_node(t_doubly_list *stack,t_env_node *node);
void print_doubly_list(t_doubly_list *stack);

#endif