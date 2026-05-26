#ifndef COMMAND_H
#define COMMAND_H

#include "parser.h"

typedef struct {
  const char *cmd;
  const char *description;
} CommandInfo;

extern const CommandInfo cmd_information[];

void handle_command(ParseInfo *parse_info);

#endif // !COMMAND_H
