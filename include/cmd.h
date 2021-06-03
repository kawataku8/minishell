#ifndef CMD_H
# define CMD_H

#include "commonlib.h"


int exec_multi_cmds(t_list *cmds_list);
pid_t	start_command(char *argv[], int ispipe, int haspipe, int lastpipe[2]);
int ispipe(t_list *cur_cmd_node);
void del_tokennode(void *content);
int exec_cmdline(t_list *cmd_list);

int my_strcmp(const char *s1, const char *s2);
char *get_value_from_envlist(char *key, t_doubly_list *env_list);
int envvar_exist(char *word, int *i, int *j);
char *get_env_value(char *word, t_doubly_list *env_list);
char *make_new_word(char *word, char *env_value);
void free_splitstr(char **str);
t_list *make_new_tokens(char *word, char *env_value);
t_list *expand_env_in_token(t_list *token, char *env_value, int flag_dquote);
void free_token(t_list *token);
void expand_env(t_list *token_list, t_doubly_list *env_list);
void edit_env(t_list *cmd_list, t_doubly_list *env_list);

#endif
