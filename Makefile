CC=gcc
CFLAGS= -Wall -Wextra

cmd: main.c input.c input.h parser.c parser.h string_util.c string_util.h command.c command.h
	$(CC) $(CFLAGS) main.c input.c parser.c string_util.c command.c -o cmd

clean:
	rm -f cmd
