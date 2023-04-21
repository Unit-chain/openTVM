//
// Created by Kirill Zhukov on 26.02.2023.
//

#ifndef VM_WITH_HEAP_OS_H
#define VM_WITH_HEAP_OS_H

#ifdef _WIN32
    #include <windows.h>
    #include <stdafx.h>
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    #define pagesize si.dwPageSize
#else
    #include <sys/mman.h>
    #include "unistd.h"
    #define pagesize (sysconf(_SC_PAGESIZE))
#endif

#endif //VM_WITH_HEAP_OS_H
