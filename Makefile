CC=gcc
CFLAGS= -Wall -Wextra
SOURCE=main.c input.c parser.c string_util.c cmd_handler.c commands.c

cmd:
	$(CC) $(CFLAGS) $(SOURCE) -o cmd -lreadline

cmd-readline:
	$(CC) $(CFLAGS) -DUSE_GNU_READLINE $(SOURCE) -o cmd -lreadline

clean:
	rm -f cmd
