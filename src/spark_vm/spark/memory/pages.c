//
// Created by Kirill Zhukov on 15.03.2023.
//
#include "pages.h"

void *pages_mmap(void *addr, size_t size) {
    void *ret;
#ifdef _WIN32
    ret = VirtualAlloc(addr, size, MEM_RESERVE | MEM_COMMIT,
                       PAGE_READWRITE);
#else
    ret = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
    return ret;
}

int pages_munmap(void *addr, size_t size) {
#ifdef _WIN32
    if (VirtualFree(addr, 0, MEM_RELEASE) == 0) {
#else
    if (munmap(addr, size) == -1) {
#endif
        time_t now = time(NULL);
        fprintf(stderr, "%ld: [ERROR] --- error while unmapping, errno: %d\n", now, errno);
        return -1;
    }
    return 1;
}

int pages_executable(void *addr, size_t size) {
#ifdef _WIN32
    if (VirtualProtect(buffer, code.size(), PAGE_EXECUTE_READ, &dummy) {
#else
    if (mprotect(addr, size, PROT_READ | PROT_EXEC) == -1) {
#endif
        time_t now = time(NULL);
        fprintf(stderr, "%ld: [ERROR] --- error while making memory executable, errno: %d\n", now, errno);
        return -1;
    }
    return 1;
}