/* Copyright (C) Alex Zhang */


#ifndef KUMA_STRING_H
#define KUMA_STRING_H


typedef struct {
    size_t  len;
    u_char *data;
} kuma_str_t;


#define kuma_tolower(c) (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define kuma_toupper(c) (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

#define kuma_string(str) { sizeof(str) - 1, (u_char *) str }
#define kuma_null_str { 0, NULL }


#endif
