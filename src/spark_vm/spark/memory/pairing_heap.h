//
// Created by Kirill Zhukov on 20.02.2023.
//

#ifndef VM_WITH_HEAP_PAIRING_HEAP_H
#define VM_WITH_HEAP_PAIRING_HEAP_H

#include "cstdlib"
#include "printf.h"
#include "pages.h"
#include "chunk.h"

#define t_offsetof(st, m) \
    ((size_t)&(((st *)0)->m))
#define SIZE_SZ (sizeof(size_t))
#define SIZE_U32 (sizeof(uint32_t))
#define chunk2mem(p) ((void*)((char*)(p) + SIZE_SZ + SIZE_U32))
//#define chunk2mem(p) (p->run_list->)
#define mem2chunk(mem) ((mchunkptr)((char*)(mem) - SIZE_SZ))

class pairingHeap {
public:
    pairingHeap() : root(nullptr) {}

    bool empty() const {
        return root == nullptr;
    }

    void *insert(void *ptr, size_t sz) {
        chunk_t newNode = (chunk_t) ptr;
        *newNode = {.size = sz};
        root = merge(root, newNode);
        return chunk2mem(newNode);
    }

    chunk_t getMin() const {
        return root;
    }

    int deleteMin() {
        if (this->root == nullptr) return -1;
        chunk_t old_root = root;
        root = mergePairs(root->child);
        root->parent = nullptr;
        delete old_root;
        return 1;
    }

    chunk_t mergePairs(chunk_t first) {
        if (first == nullptr || first->sibling == nullptr) {
            return first;
        }
        chunk_t a = first;
        chunk_t b = first->sibling;
        chunk_t rest = b->sibling;
        a->sibling = nullptr;
        b->sibling = nullptr;
        return merge(merge(a, b), mergePairs(rest));
    }

    void print() const {
        if (root == nullptr) {
            printf("Heap is empty.\n");
        } else {
            printf("Heap:\n");
        }
    }

private:
    chunk_t root;
private:
    chunk_t merge(chunk_t first, chunk_t second) {
        if (first == nullptr) {
            return second;
        } else if (second == nullptr) {
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
};

#endif //VM_WITH_HEAP_PAIRING_HEAP_H
