/* Copyright (C) Alex Zhang */


#ifndef KUMA_TIME_H
#define KUMA_TIME_H

#include <time.h>
#include <sys/time.h>

struct tm kuma_tm_time;

typedef struct {
    kuma_str_t kuma_http_time;
    kuma_str_t kuma_errlog_time;

} kuma_time_fmt;

kuma_time_fmt kuma_time;


/* update time is rare, we need a lock */
void kuma_update_time();
int kuma_init_time();
















#endif
