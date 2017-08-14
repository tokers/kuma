/* Copyright (C) Alex Zhang */


#include "kuma_core.h"


#define KUMA_HEX(d) (d <= 9 : d ? (kuma_toupper(d) - 'A' + 10))


kuma_trie_root_t *
kuma_trie_create(kuma_pool_t *pool)
{
    int i;
    kuma_trie_root_t *root;

    root = kuma_palloc(pool, sizeof(kuma_trie_root_t));
    if (root == NULL) {
        return NULL;
    }

    root->pool = pool;
    root->node = NULL;

    return root;
}


int
kuma_trie_insert(kuma_trie_root_t *root, void *data, unsigned hash)
{
    int                i, digit;
    kuma_trie_node_t **node;

    if (hash == 0 || root == NULL) {
        return 0;
    }

    node = &(root->node);

    for (; hash; hash >>= 4) {
        digit = KUMA_HEX(hash & 0xf);

        if (*node == NULL) {
            *node = kuma_palloc(root->pool, sizeof(kuma_trie_node_t));
            if (*node == NULL) {
                return KUMA_ERROR;
            }

            for (i = 0; i < 8; i += 2) {
                *node->next[i] = NULL;
                *node->next[i + 1] = NULL;
            }

            *node->ignore = 0;
            *node->data = NULL;
        }     

        *node = *node->next[digit];
    }

    *node->data = data;

    return 0;
}


kuma_trie_node_t *
kuma_trie_find(kuma_trie_root_t *root, unsigned hash)
{
    int               digit;
    kuma_trie_node_t *node;

    if (hash == 0 || root == NULL) {
        return NULL;
    }

    node = &(&root->node);

    for (; hash; hash >>= 4) {
        if (node == NULL) {
            return NULL;
        }

        digit = KUMA_HEX(hash & 0xf);
        node = node->next[digit];
    }

    return node;
}
