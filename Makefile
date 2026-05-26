CC=gcc
CFLAGS= -Wall -Wextra

cmd: main.c input.c input.h parser.c parser.h string_util.c string_util.h cmd_handler.c cmd_handler.h commands.c commands.h
	$(CC) $(CFLAGS) main.c input.c parser.c string_util.c cmd_handler.c commands.c -o cmd

clean:
	rm -f cmd
