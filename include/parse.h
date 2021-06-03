#ifndef PARSE_H
# define PARSE_H

#include "commonlib.h"

int specify_tokentype(char c);
int idx_next_squote(char *usr_input, int start);
int idx_next_dquote(char *usr_input, int start);
int idx_next_delim(char *usr_input, int start);
t_token *make_token(char *usr_input, int *i,int in_squote, int in_dquote);
t_list *make_tokenlist(char *usr_input);
void print_tokenlist(t_list *token_list);
void print_cmdlist(t_list *cmd_list);
t_list *split_tokens(t_list *token_list);
t_list *make_cmdlist(t_list *token_list);

#endif