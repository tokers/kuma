/* Copyright (C) Alex Zhang */


#ifndef KUMA_PALLOC_H
#define KUMA_PALLOC_H


typedef kuma_pool_large_s kuma_pool_large_t;
struct kuma_pool_large_s {
    char              *data;
    kuma_pool_large_t *next;
};

typedef kuma_pool_t_list_s kuma_pool_t_list_t;
struct kuma_pool_t_list_s {
    kuma_pool_t        *kuma_pool;
    kuma_pool_t_list_t *next;

};

typedef void *(*kuma_large_alloc_pt)(size_t size);
typedef struct {
    char               *start;
    char               *pos;
    size_t              num;
    int                 slot;
    int                 rest;
    kuma_pool_large_t  *large;
    kuma_pool_t_list_t  item;
} kuma_pool_t;


kuma_pool_t *kuma_create_pool(int num);
void kuma_destroy_pool(kuma_pool_t *p);
void *kuma_palloc(kuma_pool_t *p, size_t size);



#endif
