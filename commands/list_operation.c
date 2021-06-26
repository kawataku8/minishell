
#include "../include/command.h"

// void insert_after(t_env_list *stack, t_env_node *node, t_env_node *new_node)
// {
// 	new_node->prev = node;
// 	new_node->next = node->next;
// 	if (node->next == NULL)
// 		stack->tail = new_node;
// 	else
// 		node->next->prev = new_node;
// 	node->next = new_node;
// }

// void insert_before(t_env_list *stack, t_env_node *node, t_env_node *new_node)
// {
// 	new_node->prev = node->prev;
// 	new_node->next = node;
// 	if (node->prev == NULL)
// 		stack->head = new_node;
// 	else
// 		node->prev->next = new_node;
// 	node->prev = new_node;
// }

// void insert_beginning(t_env_list *stack, t_env_node *new_node)
// {
// 	if (stack->head == NULL)
// 	{
// 		stack->head = new_node;
// 		stack->tail = new_node;
// 		new_node->prev = NULL;
// 		new_node->next = NULL;
// 	}
// 	else
// 		insert_before(stack,stack->head, new_node);
// }

t_env_node *make_env_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	new_node->key = strdup(key);
	if (!new_node || !new_node->key)
		exit(malloc_error());
	if (value == NULL)
		new_node->value = NULL;
	else
	{
		new_node->value = strdup(value);
		if (!new_node->value)
			exit(malloc_error());
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

// void insert_end(t_env_list *list, t_env_node *new_node)
// {
// 	if ((list->head == NULL) && (list->tail == NULL))
// 	{
// 		list->head = new_node;
// 		list->tail = new_node;
// 		new_node->prev = NULL;
// 		new_node->next = NULL;
// 	}
// 	else
// 	{
// 		new_node->prev = list->tail;
// 		list->tail->next = new_node;
// 		list->tail = new_node;
// 	}
// }