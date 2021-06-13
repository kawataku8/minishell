#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void	put_string_fd(char *str, int fd);
void	put_endl(int fd);

typedef struct	s_env_node
{
	char				*key;           // ノードに格納されるkey
	char				*value;         // ノードに格納されるデータ
	struct s_env_node	*next;    // 次のノードへの参照（最後尾の場合は null）
	struct s_env_node	*prev;    // 前のノードへの参照（先頭の場合は null）
}				t_env_node;

typedef struct      s_list
{
    t_env_node *head;       //双方向リストの先頭を指すアドレス
    t_env_node *tail;       //双方向リストの末尾を指すアドレス
}                   t_list;

t_env_node *make_node(char *key, char *value)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	node->key = strdup(key);
	node->value = strdup(value);
	node->next = NULL;
	return (node);
}

void insert_end(t_list *list, t_env_node *new_node)
{
	t_env_node *node;

	if ((list->head == NULL) && (list->tail == NULL))
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

void	ft_env(t_list *list)
{
	t_env_node	*ndptr;

	ndptr = list->head;
	while (ndptr != NULL)
	{
		//値がない環境変数は表示しない
		if (ndptr->value)
		{
			put_string_fd(ndptr->key, 1);
			put_string_fd("=", 1);
			put_string_fd(ndptr->value, 1);
			put_endl(1);
		}
		ndptr = ndptr->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_list		env_list;
	t_env_node	*ndptr;
	t_env_node	*node;

	env_list.head = NULL;
	env_list.tail = NULL;

	ndptr = make_node("TEST", "success");
	insert_end(&env_list, ndptr);
	node = make_node("PWD", getenv("PWD"));
	insert_end(&env_list, node);
	node = make_node("OLDPWD", getenv("OLDPWD"));
	insert_end(&env_list, node);
	ft_env(&env_list);
}