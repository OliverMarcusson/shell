#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool read_line(char *buffer, size_t size) {
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

  return true;
}
