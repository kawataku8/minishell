#ifndef CMD_H
# define CMD_H

#include "commonlib.h"
#include "setup.h"

int ispipe(t_cmd_node *cur_cmd_node);
void del_cmdnode(void *content);
pid_t	start_command(t_cmd_node *cmd_node, int haspipe, int lastpipe[2]);
t_list *exec_multi_cmds(t_list *cmd_list, t_env_list *env_list);


char **init_ft_cmd_names(void);
int exec_mycmds(int index, t_cmd_node *cmd_node,t_env_list *env_list);
int get_ft_buildin_idx(char **argv);
void execute_buildin(t_cmd_node *cmd_node, t_env_list *env_list);
void exec_single_cmd(t_cmd_node *cmd_node, t_env_list *env_list);


int my_strcmp(const char *s1, const char *s2);
char *get_value_from_envlist(char *key, t_env_list *env_list);
int envvar_exist(char *word, int *i, int *j);
char *get_env_value(char *word, t_env_list *env_list);
char *make_new_word(char *word, char *env_value);
void free_splitstr(char **str);
t_list *make_new_tokens(char *word, char *env_value);
t_list *expand_env_in_token(t_list *token, char *env_value, int flag_dquote);
void free_token(t_list *token);
void expand_env(t_list *token_list, t_env_list *env_list);
void edit_env(t_list *cmd_list, t_env_list *env_list);

int process_cmdlist(t_list *cmd_list, t_env_list *env_list);

#endif
