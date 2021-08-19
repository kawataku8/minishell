CC = gcc
CFLAGS = -I $(shell brew --prefix readline)/include
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib

all:
	$(CC) $(CFLAGS) $(LDFLAGS) FORK_STUDY.c