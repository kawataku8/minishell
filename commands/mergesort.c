#include "command.h"
#include <unistd.h>

t_env_node	*merge(t_env_node *a, t_env_node *b)
{
	t_env_node	*x;
	t_env_node	*result;
	int			len;
	t_env_list	list;


	len = ft_strlen(a->key);
	if (len >= ft_strlen(b->key))
		len = ft_strlen(b->key);

	// x = a;
	// printf("xxxx\n%s\n", a->key);
	// printf("\n%s\n", list.head->key);
	// printf("%s\nxxxx\n", x->key);


	while (a != NULL && b != NULL)
	{
		if (ft_strncmp(a->key, b->key, len) > 0)
		{
			x = make_node(a->key, a->value);
			a = a->next;
		}
		else
		{
			x = make_node(b->key, b->value);
			b = b->next;
		}
		insert_end(&list, x);
		// if (ft_strncmp(a->key, b->key, len) > 0)
		// {
		// 	x = a;
		// 	if (result == NULL)
		// 		result = x;
		// 	x = x->next;
		// 	a = a->next;
		// }
		// else
		// {
		// 	write(1,"x", 1);
		// 	x = b;
		// 	if (result == NULL)
		// 		result = x;
		// 	x = x->next;
		// 	b = b->next;
		// }
	}
	// if (a == NULL)
	// {
	// 	x = b;
	// }
	// else
	// {
	// 	x = a;
	// }

	result = list.head;
	// while (result)
	// {
	// 	printf("%s\n", result->key);
	//  	result = result->next;
	// }
	return (result);
}

t_env_node	*merge_sort_rec(t_env_node *head)
{
	t_env_node	*slow;
	t_env_node	*fast;
	t_env_node	*x;
	t_env_node	*h;
	
	/*
	**再帰の終了条件。先頭を示すheadの次がない⇨要素は残りひとつ。
	**なぜ先頭がNULLのパターンが必要かは不明
	*/
	if (head == NULL || head->next == NULL)
	{
		return (head);
	}
	slow = head;
	fast = head->next;
	if (fast != NULL)
		fast = fast->next;
	while (fast != NULL)
	{
		slow = slow->next;
		fast = fast->next;
		if (fast != NULL)
			fast = fast->next;
	}
	/*
	**fastはslowの二倍の速さで進むので、
	**fastが終端に着いた時、slowは真ん中。
	**
	**    a     b
	** 123456789
	**      ↓
	**    h  a
	** 1) 1234N
	**    x    b
	** 2) 56789N
	**
	*/
	x = slow->next;
	slow->next = NULL;

	h = head;
	printf("---------");
	while (h)
	{
		printf("%s\n", h->key);
		h = h->next;
	}
	printf("---------");
	return  merge(merge_sort_rec(head), merge_sort_rec(x));
}

void	merge_sort(t_env_list *list)
{
	t_env_node *head;

	if (list == NULL)
		return;
	head = list->head;
	merge_sort_rec(head);
}
