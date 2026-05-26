#include "command.h"
#include "parser.h"
#include "string_util.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const CommandInfo cmd_information[] = {
    {"echo", "Prints the supplied argument to the screen."},
    {"pwd", "Prints the working directory."},
    {"ls", "Lists the files and directories in the current working directory."},
    {"cd", "Changes the working directory to the supplied one."},
    {"man", "Displays manual for the provided command,"},
    {"cat", "Prints the contents of the supplied file to the console."},
    {"head", "Prints the first ten lines of the supplied file to the console."},
    {"rm", "Erases the supplied file from disk."},
    {"cp", "Copies the supplied file to the supplied destination."},
    {"mv", "Moves the supplied file to the supplied destination."},
    {"help", "Displays the help message."},
    {"exit", "Exits the shell."}};

const size_t cmd_info_len = sizeof(cmd_information) / sizeof(CommandInfo);

bool _is_command(char *token, char *command) {
  if (strcmp(token, command) == 0) {
    return true;
  }
  return false;
}

void echo_cmd(ParseInfo *parse_info) {
  char **args = parse_info->argv;
  for (size_t i = 1; i < parse_info->argc; i++) {
    strdequote(args[i]);
    printf("%s ", args[i]);
    fflush(stdout);
  }
  printf("\n");
}

void pwd_cmd() {
  char buf[1024];
  getcwd(buf, sizeof(buf));
  printf("%s\n", buf);
}

void ls_cmd(char *path) {
  DIR *dir = opendir(path);

  if (dir == NULL) {
    printf("ERROR: Could not stream the provided directory.\n");
    return;
  }

  struct dirent *entry = readdir(dir);

  while (entry != NULL) {
    printf("%s\n", entry->d_name);
    entry = readdir(dir);
  }

  closedir(dir);
}

void man_cmd(ParseInfo *parse_info) {
  for (size_t i = 0; i < cmd_info_len; i++) {
    if (strcmp(cmd_information[i].cmd, parse_info->argv[1]) == 0) {
      printf("%s: %s\n", parse_info->argv[1], cmd_information[i].description);
    }
  }
}

void help_cmd() {
  printf("These commands are currently available:\n");
  for (size_t i = 0; i < cmd_info_len; i++) {
    printf("%s ", cmd_information[i].cmd);
    fflush(stdout);
  }
  printf("\n");
}

void cat_cmd(char *path) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    printf("ERROR: System could not open the file specified.");
    return;
  }
}

void handle_command(ParseInfo *parse_info) {
  char *command = parse_info->argv[0];

  if (parse_info->argc == 0) {
    return;
  }

  if (_is_command(command, "exit")) {
    exit(0);
  }

  else if (_is_command(command, "echo")) {
    echo_cmd(parse_info);
  }

  else if (_is_command(command, "pwd")) {
    pwd_cmd();
  }

  else if (_is_command(command, "ls")) {
    if (parse_info->argc == 1) {
      ls_cmd(".");
    }

    else if (parse_info->argc == 2) {
      strdequote(parse_info->argv[1]);
      ls_cmd(parse_info->argv[1]);
    }

    else {
      printf("Usage: ls <optional_path>\n");
    }
  }

  else if (_is_command(command, "man")) {
    man_cmd(parse_info);
  }

  else if (_is_command(command, "help")) {
    help_cmd();
  }
}
