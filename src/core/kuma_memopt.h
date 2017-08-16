/* Copyright (C) Alex Zhang */


#ifndef KUMA_MEMEOPT_H
#define KUMA_MEMEOPT_H

#define kuma_align(d, a) ((d + (a - 1)) & ~(a - 1))

#define kuma_memcpy(dst, src, n) memcpy(dst, src, n)
#define kuma_cpymem(dst, src, n) kuma_memcpy(dst, src, n) + n


#endif
