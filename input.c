#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

bool read_line(char *buffer, size_t size) {
#ifdef USE_GNU_READLINE
  char *line = readline("$ ");
  strncpy(buffer, line, size);
  free(line);
#else
  printf("$ ");
  fflush(stdout);

  if (fgets(buffer, size, stdin) == NULL) {
    return false;
  };

  size_t len = strlen(buffer);

  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
    len--;
  }
#endif /* ifdef USE_GNU_READLINE */
  return true;
}
