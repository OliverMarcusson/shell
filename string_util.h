#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stdbool.h>

void strdequote(char *str);

bool _str_to_size_t(char *str, size_t *out);

#endif // !STRING_UTIL_H
