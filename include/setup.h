#ifndef SETUP_H
# define SETUP_H

#include "commonlib.h"
#include "setup.h"

void setup_op(t_list *cmd_list);
int count_strtoken(t_list *token);
void setup_argv_argc(t_cmd_node *cmd_node);


#endif