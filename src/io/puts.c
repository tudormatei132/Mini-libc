#include <errno.h>
#include <internal/syscall.h>
#include "../include/internal/io.h"

int puts(char *s)
{
  while (*s) {
    if (write(1, s, 1) == -1)
      return -1;
    s++;
  }
  if (write(1, "\n", 1) == -1)
    return -1;
  return 1;
}
