#ifndef __TIME_H_
#define __TIME_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

struct timespec {
  long tv_sec;
  long tv_nsec;
};

int nanosleep(const struct timespec *duration, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif
