/* Copyright (C) Alex Zhang */


#include "kuma_core.h"


kuma_vector_t *
kuma_vector_create(size_t capacity, size_t item_size, kuma_pool_t *pool)
{
    kuma_vector_t *kv;
    size_t         size;

    if (capacity == 0) {
        return NULL;
    }

    size = kuma_align(sizeof(kuma_vector_t) + capacity * item_size);

    kv = kuma_palloc(pool, size);
    if (kv == NULL) {
        return NULL;
    }

    kv->capacity = capacity;
    kv->item_size = item_size;
    kv->item_num = 0;
    kv->pool = pool;

    return kv;
}


void
kuma_vector_destroy(kuma_vector_t *kv)
{
    if (kv == NULL) {
        return;
    }

    kv->data -= kv->item_num * kv->item_size;
    kv->item_num = 0;
}


void *
kuma_vector_push(kuma_vector_t *kv)
{
    char *block;
    char *new;

    if (kv == NULL) {
        return NULL;
    }

    if (kv->item_num == kv->capacity) {
        /* vector is full */
        new = kuma_palloc(kv->pool,  kv->capacity << 1);
        kuma_memcpy(new, kv->data, kv->item_num * kv->item_size);
        kv->data = new + kv->item_num * kv->item_size;
        kv->capacity <<= 1;
    }

    kv->item_num++;
    block = kv->data;
    kv->data += kv->item_size;

    return (void *) block;
}
