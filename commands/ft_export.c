
#include "command.h"

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

void		export_env_list(t_env_list *list)
{
	char		**env_arr;
	int			envcount;
	int			i;
	t_env_node	*node;

	i = 0;
	envcount = 0;
	node = list->head;
	while (node != NULL)
	{
		envcount++;
		node = node->next;
	}
		node = list->head;
	//merge_sort(list);
	env_arr = malloc(sizeof(char*) * envcount + 1);
	node = list->head;
	while (node != NULL)
	{
		//cmpは１文字でいいのか？
		if (ft_strncmp(node->key, "_", 2))
		{
			env_arr[i] = ft_strdup(node->key);
			if (node->value)
			{
				env_arr[i] = ft_strjoin(env_arr[i], "=\"");
				env_arr[i] = ft_strjoin(env_arr[i], node->value);
				env_arr[i] = ft_strjoin(env_arr[i], "\"");
			}
			i++;
		}
		node = node->next;
	}
	env_arr[i] = NULL;

	i = 0;
	while (env_arr[i])
	{
		put_string_fd("declare -x ", 1);
		put_string_fd(env_arr[i], 1);
		put_endl(1);
		i++;
	}

	// env_arrを作る
	// 	①Keyが_のみの場合は無視（printしない）
	// 	②値がない場合はKeyのみを文字列として入れる
	// 	③Key="value"の形にして文字列を作って入れる
	// 		※"$\はそのまま文字列にして入れるとプリントできないので直前にバックスラッシュを追加する。
	// env_arrを辞書順にソートする
	// プリントする
}
 

void		ft_export(char **argv, t_env_list *list)
{
	t_env_node	*node;
	t_env_node	*ndptr;
	int			i;
	int			pos;
	char		*ptr;
	char		*keybuf;
	char		*valuebuf;
	int			flag;

	i = 1;
	if (!argv[1]) //引数なし⇨環境変数の出力
		export_env_list(list);
	else //引数あり⇨環境変数への登録
	{
		//新しノードを作成する
		//新しいノードに引数を分解して入力する, 複数入力がある場合は複数
		//既存のkeyと被っているか、値があるか判断してリストに加える。

		i++;
		while (argv[i])
		{
			pos = 0;
			if ((ptr = ft_strchr(argv[i], '=')) != NULL)
			{
				keybuf = ft_substr(argv[i], 0,	pos = ptr - argv[i]);
				valuebuf = ft_strdup(argv[i] + (ptr - argv[i] + 1));
				node = make_node(keybuf, valuebuf);
			}
			else
			{
				keybuf = ft_strdup(argv[i]);
				node = make_node(keybuf, NULL);
			}
			//リストにない場合は最後尾に入れる
			if ((ndptr = serch_nodes(list, node->key)) == NULL)
			{
				insert_end(list, node);
			}
			//リストにあるが、valueがなく、新しいnodeにvalueがある場合
			else if (ndptr && !ndptr->value && node->value)
				ndptr->value = ft_strdup(node->value);
			//リストにあり、valueもある場合、変化なし。
			i++;
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env_list	env_list;
	t_env_node	*ndptr;
	t_env_node	*node;
	t_env_node	*nd;
	char		*ptr;
	char		*keybuf;
	char		*valuebuf;


	
	while (*envp)
	{
		printf("%s\n",*envp);
		envp++;
	}

	// while (*envp)
	// {
	// 	ptr = ft_strchr(*envp, '=');
	// 	keybuf = ft_substr(*envp, 0, ptr - *envp);
	// 	valuebuf = ft_strdup(*envp + (ptr - *envp + 1));
	// 	node = make_node(keybuf, valuebuf);
	// 	//printf("declare -x %s=", node->key);
	// 	//printf("%s\n", node->value);
	// 	insert_end(&env_list, node);
	// 	node = node->next;
	// 	envp++;
	// }
	// ft_export(&env_list, argv);

	// if (argv[1])
	// {
	// 	ndptr = env_list.head;
	// 	while (ndptr)
	// 	{
	// 		printf("%s=%s\n", ndptr->key,ndptr->value);
	// 		ndptr = ndptr->next;
	// 	}
	// }
	return (0);
}