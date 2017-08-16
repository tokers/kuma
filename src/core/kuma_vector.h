/* Copyright (C) Alex Zhang */


#ifndef KUMA_VECTOR_H
#define KUMA_VECTOR_H


typedef struct {
    size_t       item_size;
    int          item_num;
    size_t       capacity;
    void        *data;
    kuma_pool_t *pool;

} kuma_vector_t;


kuma_vector_t *kuma_vector_create(size_t capacity, size_t item_size, kuma_pool_t *pool);
void *kuma_vector_push(kuma_vector_t *kv);
void kuma_vector_destroy(kuma_vector_t *kv);


#endif
