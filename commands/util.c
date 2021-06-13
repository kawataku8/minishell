#include <unistd.h>
#include "../include/command.h"

void	put_string_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

void	put_space(int fd)
{
	write(fd, " ", 1);
}

void	put_endl(int fd)
{
	write(fd, "\n", 1);
}

// t_env_node *make_node(char *key, char *value)
// {
// 	t_env_node *new_node;

// 	if (!(new_node = (t_env_node*)malloc(sizeof(t_env_node))))
// 		return (NULL);
// 	new_node->key = key;
// 	new_node->value = value;
// 	new_node->next = NULL;
// 	new_node->prev = NULL;

// 	return (new_node);
// }

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

// void insert_end(t_env_list *stack, t_env_node *new_node)
// {
// 	if (stack->tail == NULL)
// 		insert_beginning(stack, new_node);
// 	else     
// 		insert_after(stack, stack->tail, new_node);
// }

// t_env_node *make_node(char *key, char *value)
// {
// 	t_env_node	*node;

// 	node = malloc(sizeof(t_env_node));
// 	node->key = strdup(key);
// 	if (value == NULL)
// 	{
// 		node->value = NULL;
// 	}
// 	else
// 		node->value = strdup(value);		
// 	node->next = NULL;
// 	node->prev = NULL;
// 	return (node);
// }

// void insert_end(t_env_list *list, t_env_node *new_node)
// {
// 	t_env_node *node;

// 	if ((list->head == NULL) && (list->tail == NULL))
// 	{
// 		list->head = new_node;
// 		list->tail = new_node;
// 	}
// 	else
// 	{
// 		new_node->prev = list->tail;
// 		list->tail->next = new_node;
// 		list->tail = new_node;
// 	}
// }

t_env_node		*serch_nodes(t_env_list *list, char *keybuf)
{
	t_env_node		*ndptr;

	ndptr = list->head;
	while (ndptr)
	{
		if (!(ft_strncmp(ndptr->key, keybuf, ft_strlen(keybuf))))
		{
			//keyがリストの中にあった場合
			if (ndptr->value)
				return (ndptr);
		}
		ndptr = ndptr->next;
	}
	return (NULL);
}