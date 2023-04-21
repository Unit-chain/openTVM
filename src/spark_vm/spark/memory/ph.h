//
// Created by Kirill Zhukov on 13.03.2023.
//

#ifndef VM_WITH_HEAP_PH_H
#define VM_WITH_HEAP_PH_H

#include "pages.h"
#include "chunk.h"

#define DEBUG_PH true
struct phn {
    uintptr_t address; // chunk address
    void *prev;
    void *next;
    void *lchild;
};

typedef struct phn* phn_t;

struct pairing_heap {
    phn_t root;
};

typedef struct pairing_heap* pairing_heap_t;

#ifdef __cplusplus
extern "C" {
#endif

extern chunk_t merge(chunk_t first, chunk_t second);
extern chunk_t get_min(pairing_heap_t ph);

extern void *insert(pairing_heap_t ph, void *ptr, size_t sz);

extern chunk_t deleteMin(pairing_heap_t ph);
extern chunk_t mergePairs(chunk_t first);

#ifdef __cplusplus
}
#endif


#endif //VM_WITH_HEAP_PH_H
