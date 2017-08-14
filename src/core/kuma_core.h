/* Copyright (C) Alex Zhang */


#ifndef KUMA_CORE_H
#define KUMA_CORE_H

#include "kuma_string.h"
#include "kuma_time.h"
#include "kuma_size_balanced_tree.h"
#include "kuma_palloc.h"


#define KUMA_INT32_LEN sizeof("-2147483648") - 1

#define KUMA_ALIGNMENT sizeof(unsigned long)


#define KUMA_ERROR -1
#define KUMA_OK 0

unsigned kuma_pagesize;




#endif
