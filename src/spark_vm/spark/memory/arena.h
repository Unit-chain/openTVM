//
// Created by Kirill Zhukov on 11.02.2023.
//

#ifndef VM_WITH_HEAP_ARENA_H
#define VM_WITH_HEAP_ARENA_H

#include "pages.h"
#include "pairing_heap.h"
#include "rbt.h"

class arena {
public:
    arena() = default;

    void *insert_chunk(void *ptr, size_t size) {
        return this->ph.insert(ptr, size);
    }
    void *allocate_memory(size_t size) {
        void* ptr = pages_mmap(nullptr, size);

    }

private:
    pairingHeap ph{};
//    RBTree chunkTree{};
    size_t memoryAllocated{};
};

//void *allocate_memory(arena *ar, size_t size) {
//    void* page = pages_mmap(nullptr, size);
//    size_t free_memory_in_page;
//    if (size > pagesize) {
//        free_memory_in_page = size % pagesize;
//    } else {
//        free_memory_in_page = pagesize - size;
//    }
//
//}

#endif //VM_WITH_HEAP_ARENA_H
