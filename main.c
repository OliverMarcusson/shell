#include "cmd_handler.h"
#include "input.h"
#include "parser.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define INPUT_SIZE 1024
#define MAX_ARGS 8

int main() {
  char buffer[INPUT_SIZE];

  // Shell loop
  while (true) {
    if (!read_line(buffer, sizeof(buffer))) {
      break;
    }

    ParseInfo parse_info = parse_line(buffer);

    // User input nothing or some error happened
    if (parse_info.argc == 99) {
      continue;
    }

    handle_command(&parse_info);
  }

  return 0;
}
