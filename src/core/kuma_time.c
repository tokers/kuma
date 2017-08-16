/* Copyright (C) Alex Zhang */


#include "kuma_core.h"

#define kuma_gettimeofday(tv, tz) gettimeofday(tv, tz)


inline void
kuma_update_time()
{
    /*TODO lock */

    struct timeval tv;

    kuma_gettimeofday(&tv, NULL);
}


void
kuma_init_time()
{
    kuma_time.kuma_http_time = kuma_string("Mon, 1 1 1970 00:00:00 GMT")
    kuma_time.kuma_errlog_time = kuma_string("Mon, 1 1 1970 00:00:00 GMT")

    kuma_update_time();
}
