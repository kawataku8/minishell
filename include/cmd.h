#ifndef CMD_H
# define CMD_H

#include "commonlib.h"


int exec_multi_cmds(t_list *cmds_list);
pid_t	start_command(char *argv[], int ispipe, int haspipe, int lastpipe[2]);
int ispipe(t_list *cur_cmd_node);
void del_tokennode(void *content);
int exec_cmdline(t_process *cmd_list);




#endif
