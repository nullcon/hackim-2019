#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <dlfcn.h>

static bool state = false;
static time_t last_time = 0;
static time_t delay = 0;
static timeval *zero = 0;

typedef int (*orig)(struct timeval *tv, struct timezone *tz);

extern "C" int nanosleep(const struct timespec *req, struct timespec *rem) {
    delay = req->tv_sec;
    return 0;
}

extern "C" int gettimeofday(struct timeval *tv, struct timezone *tz) {
    orig gettimeofday_orig = (orig)dlsym(RTLD_NEXT, "gettimeofday");
    int retval = 0;

    if (!zero) {
        zero = new timeval;
        retval = gettimeofday_orig(zero, tz);
        *tv = *zero;
    }

    retval = gettimeofday_orig(tv, tz);

    if (!state) {
        last_time = tv->tv_sec;
        state = true;
    }

    else {
        tv->tv_sec = last_time + delay;
        state = false;
    }

    return retval;
}
