#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <internal/syscall.h>

unsigned int sleep(unsigned int seconds)
{
  // a timespec struct that will help us call nanosleep
  // since we want nanosleep to be "seconds" seconds long
  // we need to set the nsec parameter to 0
  struct timespec duration;
  duration.tv_sec = seconds;
  duration.tv_nsec = 0;
  // we will use it if the nanosleep syscall is cancelled
  // to return the remaining seconds
  struct timespec rem;

  if (nanosleep(&duration, &rem) == -1) {
    if (errno == EINTR)
      duration = rem;
    return rem.tv_sec;
  }
  return 0;
}

int nanosleep(const struct timespec *duration, struct timespec *rem)
{
  int ret = syscall(__NR_nanosleep, duration, rem);
  if (ret < 0) {
    // if the system call failed, set the errno
    errno = -ret;
    return -1;
  }
  return 0;
}
