SRCS =  ./src/main.c\
	./src/main_utils.c\
	./src/parse/tokenizer.c\
	./src/parse/tokenizer_utils.c\
	./src/parse/make_procslist.c\
	./src/parse/set_redirect_fd.c\
	./src/parse/manage_fd.c\
	./src/parse/parse_redirect.c\
	./src/parse/parse_redirect_utils.c\
	./src/parse/heredoc.c\
	./src/parse/heredoc_utils.c\
	./src/validator/validator.c\
	./src/validator/validator_utils.c\
	./src/env_operations/make_envlist.c\
	./src/env_operations/make_char_envlist.c\
	./src/env_operations/mod_envlist.c\
	./src/dlist_operations/dlist_operations.c\
	./src/dlist_operations/dlist_operations_utils.c\
	./src/setup/setup.c\
	./src/execute_comannd/process_cmdline.c\
	./src/execute_comannd/exec_single_cmd.c\
	./src/execute_comannd/exec_multi_cmds.c\
	./src/execute_comannd/exec_multi_cmds_utils.c\
	./src/execute_comannd/find_abscmd_path.c\
	./src/execute_comannd/expand_env.c\
	./src/execute_comannd/expand_env_utils1.c\
	./src/execute_comannd/expand_env_utils2.c\
	./src/signal/signal.c\
	./src/signal/readline.c\
	./commands/ft_echo.c\
	./commands/ft_pwd.c\
	./commands/ft_unset.c\
	./commands/ft_env.c\
	./commands/ft_exit.c\
	./commands/export/export_env_list.c\
	./commands/export/mergesort.c\
	./commands/export/ft_export.c\
	./commands/export/make_env_arr.c\
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