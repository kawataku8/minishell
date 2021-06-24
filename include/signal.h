#ifndef SIGNAL_H
# define SIGNAL_H

#include "commonlib.h"
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum);
void sigquit_handler(int signum);
void setup_signals(void);

#endif