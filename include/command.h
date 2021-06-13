#ifndef CONSTANTS_H
# define CONSTANTS_H

#include "../libft/libft.h"
// #include "exit_status.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "commonlib.h"

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define SUCCESS 1
# define ERROR -1

# define FALSE 0
# define TRUE 1

// typedef struct	s_env_node
// {
// 	char				*key;           // ノードに格納されるkey
// 	char				*value;         // ノードに格納されるデータ
// 	struct s_env_node	*next;    // 次のノードへの参照（最後尾の場合は null）
// 	struct s_env_node	*prev;    // 前のノードへの参照（先頭の場合は null）
// }				t_env_node;

// typedef struct      s_env_list
// {
//     t_env_node *head;       //双方向リストの先頭を指すアドレス
//     t_env_node *tail;       //双方向リストの末尾を指すアドレス
// }                   t_env_list;

void			put_string_fd(char *str, int fd);
void			put_endl(int fd);
// t_env_node		*make_node(char *key, char *value);
// void			insert_end(t_env_list *list, t_env_node *new_node);
// void			merge_sort(t_env_list *list);
// t_env_node		*serch_nodes(t_env_list *list, char *keybuf);
int				ft_cd(int argc, char **argv, t_env_list *list);
void			ft_echo(int argc, char **argv);
void			ft_env(t_env_list *list);
// // int				ft_pa_exit(char **argv, int argc);
// int				ft_ch_exit(char **argv, int argc);
// void			ft_export(char **argv, t_env_list *list);
void			ft_pwd(char **argv);
// int				ft_unset(char **argv, t_env_list *list);



#endif