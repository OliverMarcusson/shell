#include "commands.h"
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
    {"touch", "Creates a new file."},
    {"help", "Displays the help message."},
    {"exit", "Exits the shell."},
    {"clear", "Clears the console."}};

const size_t cmd_info_len = sizeof(cmd_information) / sizeof(CommandInfo);

bool _is_command(char *token, char *command) {
  if (strcmp(token, command) == 0) {
    return true;
  }
  return false;
}

bool _file_exists(char *path) {
  if (access(path, F_OK) == 0) {
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
      return;
    }
  }
  printf("ERROR: Specified command does not exist.\n");
}

void help_cmd() {
  printf("These commands are currently available:\n");
  for (size_t i = 0; i < cmd_info_len; i++) {
    printf("%s ", cmd_information[i].cmd);
    fflush(stdout);
  }
  printf("\n");
}

void cd_cmd(char *path) {
  if (chdir(path) != 0) {
    printf("ERROR: Could not change the working directory to the one "
           "specified.\n");
  }
}

void cat_cmd(char *path) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    printf("ERROR: System could not open the file specified.\n");
    return;
  }

  int c;
  while ((c = fgetc(file)) != EOF) {
    putchar(c);
  }

  printf("\n");
  fflush(stdout);

  fclose(file);
}

void clear_cmd() {
  printf("\033[2J\033[H"); // ANSI escape sequence to clear console and move
                           // cursor to the home position.
  fflush(stdout);
}

void rm_cmd(char *path) {
  if (remove(path) != 0) {
    printf("ERROR: Could not delete the specified file.\n");
  }
}

void mv_cmd(char *old_path, char *new_path) {
  if (_file_exists(new_path)) {
    printf(
        "ERROR: File with specified destination file name already exists.\n");
    return;
  }

  if (rename(old_path, new_path) != 0) {
    printf("ERROR: Could not move/rename the file.\n");
  }
}

void touch_cmd(char *path) {
  if (_file_exists(path)) {
    printf("ERROR: Specified path already exists.\n");
    return;
  }

  FILE *file = fopen(path, "wb");

  if (file == NULL) {
    printf("ERROR: Could not create the specified file.\n");
    return;
  }

  fclose(file);
}

void head_cmd(char *path, size_t lines) {
  if (!_file_exists(path)) {
    printf("ERROR: Specified file does not exist.\n");
    return;
  }

  FILE *file = fopen(path, "r");

  if (file == NULL) {
    printf("ERROR: Could not open the specified file.\n");
    return;
  }

  char line[1024];
  size_t i = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (i == lines) {
      return;
    }

    printf("%s", line);
    i++;
  }

  if (i != lines) {
    printf("\n");
  }
}

void cp_cmd(char *old_path, char *new_path) {
  FILE *src = fopen(old_path, "rb");

  if (src == NULL) {
    printf("ERROR: Could not open the source file.\n");
    return;
  }

  if (_file_exists(new_path)) {
    printf("ERROR: Destination file already exists.\n");
    fclose(src);
    return;
  }

  FILE *dest = fopen(new_path, "wb");

  if (dest == NULL) {
    printf("ERROR: Could not open the destination file.\n");
    fclose(src);
    return;
  }

  int c;
  while ((c = fgetc(src)) != EOF) {
    if (fputc(c, dest) == EOF) {
      printf("ERROR: Could not copy character from source file to destination "
             "file.\n");
      fclose(src);
      fclose(dest);
      return;
    }
  }

  fclose(src);
  fclose(dest);
}
