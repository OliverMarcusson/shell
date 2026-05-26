#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

bool _string_in_quotations(char *str) {
  if (str[0] == '\'' && str[strlen(str) - 1] == '\'') {
    return true;
  }
  if (str[0] == '"' && str[strlen(str) - 1] == '"') {
    return true;
  }
  return false;
}

void strdequote(char *str) {
  size_t len = strlen(str);

  if (!_string_in_quotations(str)) {
    return;
  }

  if (len < 2) {
    return;
  }
  memmove(str, str + 1, len - 2);
  str[len - 2] = '\0';
}

bool _str_to_size_t(char *str, size_t *out) {
  if (str == NULL || str[0] == '\0') {
    return false;
  }

  char *endptr;
  errno = 0;

  unsigned long value = strtoul(str, &endptr, 10);
  
  // If conversion failed
  if (errno != 0) {
    return false;
  }

  // endptr will be set to \0 if value str was numeric, and something else if it was not
  if (*endptr != '\0') {
    return false;
  }

  *out = (size_t) value;
  return true;
}
