#ifndef MAIN_H
# define MAIN_H

#include <readline/readline.h>
#include <readline/history.h>

void	del_token(void *content);
void	free_cmdlist(t_list **cmd_list);
int	manage_usr_input(char *usr_input, t_env_list *env_list);
t_list	*pre_process(char **usr_input, t_env_list *env_list, int *bc_flag);

char	*trim_usr_input(char *usr_input);
t_list	*manage_tokenlist(char *usr_input);
t_list	*manage_cmdlist(t_list *token_list, t_env_list *env_list);
void	my_add_history(char *usr_input);

#endif