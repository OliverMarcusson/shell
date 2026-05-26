#include "cmd_handler.h"
#include "commands.h"
#include "parser.h"
#include "string_util.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

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
    if (parse_info->argc != 2) {
      printf("Usage: man <command>\n");
      return;
    }

    man_cmd(parse_info);
  }

  else if (_is_command(command, "help")) {
    help_cmd();
  }

  else if (_is_command(command, "cd")) {
    if (parse_info->argc == 1) {
      char *home = getenv("HOME");
      if (home == NULL) {
        printf("WARN: HOME is not set, cannot change working directory to home directory.\n");
        return;
      }
      
      cd_cmd(home);
      return;
    }

    if (parse_info->argc != 2) {
      printf("Usage: cd <optional-path>\n");
      return;
    }

    cd_cmd(parse_info->argv[1]);
  }

  else if (_is_command(command, "clear")) {
    clear_cmd();
  }

  else if (_is_command(command, "cat")) {
    if (parse_info->argc != 2) {
      printf("Usage: cat <path>\n");
      return;
    }

    cat_cmd(parse_info->argv[1]);
  }

  else if (_is_command(command, "rm")) {
    if (parse_info->argc != 2) {
      printf("Usage: rm <path>\n");
      return;
    }

    rm_cmd(parse_info->argv[1]);
  }

  else if (_is_command(command, "mv")) {
    if (parse_info->argc != 3) {
      printf("Usage: mv <old_path> <new_path>\n");
      return;
    }

    mv_cmd(parse_info->argv[1], parse_info->argv[2]);
  }

  else if (_is_command(command, "touch")) {
    if (parse_info->argc != 2) {
      printf("Usage: touch <path>\n");
      return;
    }

    touch_cmd(parse_info->argv[1]);
  }

  else if (_is_command(command, "head")) {
    if (parse_info->argc < 2) {
      printf("Usage: head <path> <optional-line-count>\n");
      return;
    }

    if (parse_info->argc == 2) {
      head_cmd(parse_info->argv[1], 10);
      return;
    }

    size_t lines = 0;
    if (!_str_to_size_t(parse_info->argv[2], &lines)) {
      printf("ERROR: lines must be numerical.\n");
      return;
    }
    
    head_cmd(parse_info->argv[1], lines);
  }

  else if (_is_command(command, "cp")) {
    if (parse_info->argc != 3) {
      printf("Usage: cp <old_path> <new_path>\n");
      return;
    }

    cp_cmd(parse_info->argv[1], parse_info->argv[2]);
  }
}
