// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <internal/types.h>

int open(const char *filename, int flags, ...)
{
  int fd;
  if (flags & O_CREAT) {
    // it means we have an additional argument
    // which will be a mode_t type
    va_list args;
    va_start(args, flags);
    mode_t mode = va_arg(args, mode_t);
    fd = syscall(__NR_open, filename, flags, mode);
    va_end(args);
  } else {
    fd = syscall(__NR_open, filename, flags);
  }

  if (fd < 0) {
    errno = -fd;
    return -1;
  }

  return fd;
}
