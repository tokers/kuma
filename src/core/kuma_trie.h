/* Copyright (C) Alex Zhang */


#ifndef KUMA_TRIE_H
#define KUMA_TRIE_H


typedef struct {
    void        *data;
    int         *next[16];
    int          ignore:1;
} kuma_trie_node_t;


typedef struct {
    kuma_trie_node_t *node;
    kuma_pool_t      *pool;
} kuma_trie_root_t;


kuma_trie_root_t *kuma_trie_create(kuma_pool_t *pool);
int kuma_trie_insert(kuma_trie_root_t *root, void *data, unsigned hash);
kuma_trie_node_t *kuma_trie_find(kuma_trie_root_t *root, unsigned hash);


#endif
