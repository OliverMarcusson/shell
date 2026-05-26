#include <stdbool.h>
#include <string.h>

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
