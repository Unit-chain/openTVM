//
// Created by Kirill Zhukov on 03.02.2023.
//

#ifndef VM_WITH_HEAP_CHUNK_H
#define VM_WITH_HEAP_CHUNK_H

#include "stdio.h"
#include "os.h"
#include "m_bitmap.h"

#define SIZE_SZ (sizeof(size_t))
#define SIZE_U32 (sizeof(uint32_t))
#if 0
    #define chunk2mem(p) ((void*)((char*)(p) + SIZE_SZ + SIZE_U32))
#endif
#define CHUNK_SIZE (2 * 1024 * 1024) // 2 MB
#define PAGES_IN_RUN
#define ALIGNMENT(s, alignment) \
            (((s) + (alignment - 1)) & (-(alignment)))
struct run;
struct chunk;
typedef struct chunk *chunk_t;
typedef struct arena* arena_t;
typedef struct run *run_t;

struct run {
    size_t length;
    char *start;
    run_t next;
    run_t previous;
    uint32_t nfree,
            nregs:31;
    uint32_t dirty;
};

struct chunk {
    size_t size;
    uint32_t freeSize;
    run_t *run_list;
    uint64_t last_used;
    uint32_t nruns;
    struct chunk *parent;
    struct chunk *child;
    struct chunk *sibling;
    void *runs[]; // [1]. find Flexible array member
};

#ifdef __cplusplus
extern "C" {
#endif

extern void setChunkSize(chunk_t ch, size_t sz);

#ifdef __cplusplus
}
#endif

#endif //VM_WITH_HEAP_CHUNK_H
