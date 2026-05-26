#include "parser.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool _cmd_in_commands(char *cmd) {
  const char *commands[] = {
      "echo",  "pwd", "ls", "cd", "man",  "cat",  "head",
      "touch", "rm",  "cp", "mv", "help", "exit", "clear",
  };

  size_t command_count = sizeof(commands) / sizeof(commands[0]);

  for (size_t i = 0; i < command_count; i++) {
    if (strcmp(commands[i], cmd) == 0) {
      return true;
    }
  }

  return false;
}

ParseInfo parse_line(char *buffer) {
  ParseInfo parse_info;

  char *token = strtok(buffer, " \t\n");

  // If the buffer is empty
  if (token == NULL) {
    parse_info.argc = 99;
    return parse_info;
  }

  // If command is not found
  if (!_cmd_in_commands(token)) {
    printf("Command '%s' not recognized. Type 'help' for a list of commands.\n",
           token);
    parse_info.argc = 99;
    return parse_info;
  }

  parse_info.argv[0] = token;
  parse_info.argc = 1;
  token = strtok(NULL, " \t\n"); // Advances the string "splitting"

  // While there are still tokens left in the buffer
  while (token != NULL) {
    if (parse_info.argc == 8) {
      printf("WARN: Maximum arguments reached. Output may be truncated.\n");
      break;
    }

    parse_info.argv[parse_info.argc] = token;
    parse_info.argc++;

    token = strtok(NULL, " \t\n"); // Advances the string "splitting"
  }

  return parse_info;
}
