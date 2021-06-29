SRCS =  ./src/main.c\
	./src/parse/tokenizer.c\
	./src/parse/make_procslist.c\
	./src/parse/set_redirect_fd.c\
	./src/parse/manage_fd.c\
	./src/validator/validator.c\
	./src/execute_comannd/expand_env.c\
	./src/env_operations/make_envlist.c\
	./src/dlist_operations/dlist_operations.c\
	./src/setup/setup.c\
	./src/execute_comannd/process_cmdline.c\
	./src/execute_comannd/exec_single_cmd.c\
	./src/execute_comannd/exec_multi_cmds.c\
	./src/signal/signal.c\
	./commands/ft_echo.c\
	./commands/ft_pwd.c\
	./commands/ft_unset.c\
	./commands/ft_env.c\
	./commands/ft_exit.c\
	./commands/export/export_env_list.c\
	./commands/export/mergesort.c\
	./commands/export/ft_export.c\
	./commands/cd/ft_cd.c\
	./commands/cd/set_pwd_oldpwd.c\
	./commands/util.c\
	./commands/list_operation.c

OBJS    = $(SRCS:.c=.o)
NAME    = minishell
CC      = gcc
RM      = rm -f
CFLAGS = -I $(shell brew --prefix readline)/include
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) bonus -C ./libft
	$(CC) $(OBJS)  $(CFLAGS) $(LDFLAGS) ./libft/libft.a -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) minishell.a

re: fclean all

.PHONY: all clean fclean re .c.o