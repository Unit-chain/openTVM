//
// Created by Kirill Zhukov on 04.02.2023.
//

#ifndef VM_WITH_HEAP_PAGES_H
#define VM_WITH_HEAP_PAGES_H
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "os.h"
#ifdef _WIN32
    #include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void *pages_mmap(void *addr, size_t size);
/// @brief deallocating memory
/// @returns 0 when success, otherwise -1
extern int pages_munmap(void *addr, size_t size);
/// @brief need for JIT.
extern int pages_executable(void *addr, size_t size);

#ifdef __cplusplus
}
#endif

#endif //VM_WITH_HEAP_PAGES_H
