#ifndef COMMANDS_H
#define COMMANDS_H

#include "parser.h"
#include <stddef.h>

typedef struct {
  const char *cmd;
  const char *description;
} CommandInfo;

extern const CommandInfo cmd_information[];

bool _is_command(char *token, char *command);

bool _str_to_size_t(char *str, size_t *out);

void echo_cmd(ParseInfo *parse_info);

void pwd_cmd();

void ls_cmd(char *path);

void man_cmd(ParseInfo *parse_info);

void help_cmd();

void cd_cmd(char *path);

void cat_cmd(char *path);

void clear_cmd();

void rm_cmd(char *path);

void mv_cmd(char *old_path, char *new_path);

void touch_cmd(char *path);

void head_cmd(char *path, size_t lines);

void cp_cmd(char *old_path, char *new_path);

#endif

