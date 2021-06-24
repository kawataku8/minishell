SRCS =  ./SIGNAL_STUDY2.c

OBJS    = $(SRCS:.c=.o)
NAME    = mytest
CC      = gcc 
RM      = rm -f
CFLAGS = -I $(shell brew --prefix readline)/include
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) mytest.a

re: fclean all

.PHONY: all clean fclean re .c.o