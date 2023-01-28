#include <iostream>
#include <future>
#include <cstdio>
#include <sys/mman.h>
#include "logger/loggerTime.h"
#include "logger/logger.h"
#include "iostream"
#include "sstream"
#include "spark/memory/alloc.h"
#include "globalDefenitions.h"


#define print(x) puts(#x)
#define concat(x, y) print(x##y)

#define MEMORY_TYPES_DO(f)                                                           \
  /* Memory type by sub systems. It occupies lower byte. */                          \
  f(mtJavaHeap,       "Java Heap")   /* Java heap                                 */ \

void* alloc_writable_memory(size_t size) {
    void* ptr = mmap(0, size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == (void*)-1) {
        perror("mmap");
        return NULL;
    }
    return ptr;
}

// RX to aligned memory
// 0 = success, -1 - error
int make_memory_executable(void* m, size_t size) {
    if (mprotect(m, size, PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect");
        return -1;
    }
    return 0;
}
void emit_code_into_memory(unsigned char* m) {
//    objdump -d add4.o
//    0000000000000000 <ltmp0>:
//    0: ff 43 00 d1  	sub	sp, sp, #16
//    4: e0 07 00 f9  	str	x0, [sp, #8]
//    8: e8 07 40 f9  	ldr	x8, [sp, #8]
//    c: 08 11 00 91  	add	x8, x8, #4
//    10: e0 03 08 aa  	mov	x0, x8
//    14: ff 43 00 91  	add	sp, sp, #16
//    18: c0 03 5f d6  	ret
    unsigned char code[] = {
        0xff, 0x43, 0x00, 0xd1,
        0xe0, 0x07, 0x00, 0xf9,
        0xe8, 0x07, 0x40, 0xf9,
        0x08, 0x11, 0x00, 0x91,
        0xe0, 0x03, 0x08, 0xaa,
        0xff, 0x43, 0x00, 0x91,
        0xc0, 0x03, 0x5f, 0xd6
    };
    memcpy(m, code, sizeof(code));
}

const size_t SIZE = 1024;
typedef int (*JittedFunc)(long);

int main() {
    void* m = alloc_writable_memory(SIZE);
    emit_code_into_memory((unsigned char *) m);
    make_memory_executable(m, SIZE);

    JittedFunc func = (JittedFunc)m;
    int result = func(2);
    printf("result = %d\n", result);
#if 0
        std::string test_err = "test_string";
        log(test_err.c_str(), LoggingLevel::INFO, stdout);
        log(test_err.c_str(), LoggingLevel::ERROR, stdout);
        log(test_err.c_str(), LoggingLevel::WARN, stdout);
        log(test_err.c_str(), LoggingLevel::TRACE, stdout);
        log(test_err.c_str(), LoggingLevel::DEBUG, stdout);
        log(test_err.c_str(), "dwaddwdawa", stdout);
        concat(10,50);
        print(10);
#endif

#if 0
    int a = 10;
    auto p = (uintptr_t) &a;
    auto pt = (long) &a;
    std::cout << &a << std::endl;
    std::cout << p << std::endl;
    std::cout << *reinterpret_cast<int*>(p) << std::endl;

    std::cout << pt << std::endl;
    std::cout << *reinterpret_cast<int*>(pt) << std::endl;
#endif

    return 0;
}