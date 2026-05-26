#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

typedef struct {
  size_t argc;
  char *argv[8];
} ParseInfo;

ParseInfo parse_line(char *buffer);

#endif // !PARSER_H
