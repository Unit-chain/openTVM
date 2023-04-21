//
// Created by Kirill Zhukov on 13.03.2023.
//
#include "ph.h"

extern chunk_t merge(chunk_t first, chunk_t second) {
    if (first == NULL) {
        return second;
    } else if (second == NULL) {
        return first;
    } else {
        if (first->size < second->size) {
            second->sibling = first->child;
            first->child = second;
            second->parent = first;
            return first;
        } else {
            first->sibling = second->child;
            second->child = first;
            first->parent = second;
            return second;
        }
    }
}

extern void *insert(pairing_heap_t ph, void *ptr, size_t sz) {
    chunk_t newNode = (chunk_t) ptr;
    setChunkSize(newNode, sz);
    ph->root = merge(ph->root, newNode);
//    return chunk2mem(newNode);
    return NULL;
}

extern chunk_t get_min(pairing_heap_t ph) {
    return ph->root;
}

extern chunk_t deleteMin(pairing_heap_t ph) {
    if (ph->root == NULL) return NULL;
    chunk_t old_root = ph->root;
    ph->root = mergePairs(ph->root->child);
    ph->root->parent = NULL;
#if DEBUG_PH
    free(old_root); /// cannot use due fragmentation
#endif
    return old_root;
}

extern chunk_t mergePairs(chunk_t first) {
    if (first == NULL || first->sibling == NULL) {
        return first;
    }
    chunk_t a = first;
    chunk_t b = first->sibling;
    chunk_t rest = b->sibling;
    a->sibling = NULL;
    b->sibling = NULL;
    return merge(merge(a, b), mergePairs(rest));
}

void printNode(const chunk_t *node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("-> %lu bytes at %lu\n", node->size, node->address);
    if (node->child != nullptr) {
        if (node->parent != nullptr) {
            printf("child of  %lu", node->parent->address, "");
        }
        printNode(node
                          ->child, depth + 1);
    }
    if (node->sibling != nullptr) {
        printf("sibling of %lu", node->parent->address, "");
        printNode(node
                          ->sibling, depth);
    }
}