//
// Created by Kirill Zhukov on 27.12.2022.
//

#ifndef VM_WITH_HEAP_ALLOC_H
#define VM_WITH_HEAP_ALLOC_H
#include <stdio.h>
#include <sys/mman.h>
#include <csignal>
#include "logger/logger.h"
#include "share/s_tni.h"

extern "C" {
    /// @param obj_size size_t. amount of memory to be allocated
    tvalue *allocate_memory(size_t obj_size) {
        // virtual alloc for win: https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
//        const size_t page_size = os::vm_page_size();
        void *ptr = mmap(NULL, obj_size * sizeof(tvalue*), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
        if (ptr == MAP_FAILED) {
//            munmap(ptr, page_size);
            log("mapping failed", LoggingLevel::ERROR, stdout);
            return NULL;
        }
        #if DEBUG_MODE
                char obj_address[18];
                snprintf(obj_address, (size_t) 18, "%p", ptr);
                size_t obj_len = strlen(obj_address);
                char *msg = (char*) malloc(obj_len + 10);
                strcpy(msg, obj_address);
                strcat(msg, " allocated");
                log(msg, LoggingLevel::INFO, stdout);
                free(msg);
        #endif

    //    int N=5;
    //    int *ptr = (int *) mmap ( NULL, N*sizeof(int),
    //                      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
    //
    //    if(ptr == MAP_FAILED){
    //        printf("Mapping Failed\n");
    //        return 1;
    //    }
    //
    //    for(int i=0; i<N; i++)
    //        ptr[i] = i*10;
    //
    //    for(int i=0; i<N; i++)
    //        printf("[%d] ",ptr[i]);
    //
    //    printf("\n");
    //    int err = munmap(ptr, 10*sizeof(int));
    //    if(err != 0){
    //        printf("UnMapping Failed\n");
    //        return 1;
    //    }

    }

    /// @param obj_memory void *. object to be deallocated.
    void dealloc_memory(tvalue *obj_memory) {
        #if DEBUG_MODE
            char obj_address[18];
            snprintf(obj_address, (size_t) 18, "%p", obj_memory);
            size_t obj_len = strlen(obj_address);
            char *msg = (char*) malloc(obj_len + 12);
            strcpy(msg, obj_address);
            strcat(msg, " deallocated");
            log(msg, LoggingLevel::INFO, stdout);
            free(msg);
        #endif
        if(munmap(obj_memory, 10*sizeof(int)) != 0)
            log("unmapping failed", LoggingLevel::ERROR, stdout);
        free(obj_memory);
        obj_memory = NULL;
    }
};

#endif //VM_WITH_HEAP_ALLOC_H
