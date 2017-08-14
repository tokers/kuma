/* Copyright (C) Alex Zhang */


#include "kuma_core.h"
#include <malloc.h>


#define KUMA_POOL_PAGE_MAX_NUM 128


static void kuma_pool_t_pool_init();


kuma_pool_t_list_t *kuma_pool_t_head[KUMA_POOL_PAGE_MAX_NUM];


static void
kuma_pool_t_pool_init()
{
    int i;

    for (i = 0; i < KUMA_POOL_PAGE_MAX_NUM; i++) {
        kuma_pool_t_head[i] = NULL;
    }
}


kuma_pool_t *
kuma_create_pool(int num)
{
    kuma_pool_t *p;
    unsigned     size;

    if (num <= 0 || num > KUMA_POOL_PAGE_MAX_NUM) {
        return NULL;
    }

    if (kuma_pool_t_head[num] != NULL) {
        p = kuma_pool_t_head[num]->kuma_pool;
        kuma_pool_t_head[num] = kuma_pool_t_head[num]->next;

        return p;
    }

    size = num * kuma_pagesize;
    size += kuma_align(sizeof(kuma_pool_t), KUMA_ALIGNMENT);

    p = malloc(size);
    if (p == NULL) {
        return NULL;
    }

    p->start = p + kuma_align(sizeof(kuma_pool_t), KUMA_ALIGNMENT);
    p->pos = p->start;
    p->slot = 0;
    p->num = num;
    p->rest = kuma_pagesize;
    p->large_alloc = kuma_large_alloc;
    p->large = NULL;
    p->item.next = NULL;
    p->item.kuma_pool = p;

    return p;
}


void
kuma_destroy_pool(kuma_pool_t *p)
{
    kuma_pool_large_t *large;

    if (p == NULL) {
        return;
    }

    large = p->large;
    while (large) {
        if (large->data) {
            free(large->data);
            large->data = NULL;
        }

        large = large->next;
    }

    p->slot = 0;
    p->pos = p->start;

    p->item.next = kuma_pool_t_head[p->num];
    kuma_pool_t_head[p->num] = p;
}


void *
kuma_palloc(kuma_pool_t *p, size_t size)
{
    if (size == 0) {
        return NULL;
    }

    if (size <= (kuma_pagesize >> 1)) {
        return kuma_palloc_small(p, size);
    }

    return kuma_palloc_large(p, size);
}
