SRCS =  ./src/main.c\
	./src/parse/tokenizer.c\
	./src/parse/make_procslist.c\
	./src/validator/validator.c\
	./src/execute_comannd/expand_env.c\
	./src/env_operations/make_envlist.c\
	./src/dlist_operations/dlist_operations.c\
	./src/setup/setup.c\
	./src/execute_comannd/process_cmdline.c\
	./src/execute_comannd/exec_single_cmd.c\
	./src/execute_comannd/exec_multi_cmds.c

OBJS    = $(SRCS:.c=.o)
NAME    = minishell
CC      = gcc -g 
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) bonus -C ./libft
	$(CC) $(OBJS) -lreadline ./libft/libft.a -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) minishell.a

re: fclean all

.PHONY: all clean fclean re .c.o