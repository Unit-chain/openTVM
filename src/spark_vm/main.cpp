#include <iostream>
#include <future>
#include <cstdio>
#include <sys/mman.h>
#include "iostream"
#include "sstream"
#include "boost/multiprecision/cpp_int.hpp"
#include "share/s_ti.h"

using namespace boost::multiprecision;

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


void emit_code_into_memory_u256(unsigned char* m) {
    unsigned char code[] = {
            0xff, 0x83, 0x00, 0xd1,
            0xfd, 0x7b, 0x01, 0xa9,
            0xfd, 0x43, 0x00, 0x91,
            0xe9, 0x03, 0x08, 0xaa,
            0xe9, 0x07, 0x00, 0xf9,
            0xe1, 0x13, 0x00, 0x91,
            0x89, 0x00, 0x80, 0x52,
            0xe9, 0x07, 0x00, 0xb9,
            0x00, 0x00, 0x00, 0x94,
            0xfd, 0x7b, 0x41, 0xa9,
            0xff, 0x83, 0x00, 0x91,
            0xc0, 0x03, 0x5f, 0xd6
    };
    memcpy(m, code, sizeof(code));
}

void emit_code_into_memory_u128(unsigned char* m) {
    unsigned char code[] = {
            0xff, 0x43, 0x00, 0xd1,
            0xe1, 0x07, 0x00, 0xf9,
            0xe0, 0x03, 0x00, 0xf9,
            0xe8, 0x07, 0x40, 0xf9,
            0xe9, 0x03, 0x40, 0xf9,
            0x20, 0x11, 0x00, 0xb1,
            0x09, 0x00, 0x80, 0xd2,
            0x01, 0x01, 0x09, 0xba,
            0xff, 0x43, 0x00, 0x91,
            0xc0, 0x03, 0x5f, 0xd6
    };
    memcpy(m, code, sizeof(code));
}

const size_t SIZE = 4096;
typedef int (*JittedFunc)(long);
typedef uint256_t (*JittedFuncU256)(uint256_t);
typedef tuint128 (*JittedFuncU128)(tuint128);
typedef uint128_t (*testU)(uint128_t);

#ifdef __SIZEOF_INT128__
// do some fancy stuff here
#else
// do some fallback stuff here
#endif

int main() {
//    void* m = alloc_writable_memory(SIZE);
//    emit_code_into_memory((unsigned char *) m);
//    make_memory_executable(m, SIZE);
//
//    JittedFunc func = (JittedFunc)m;
//    int result = func(2);
//    printf("result = %d\n", result);

    char myRandomData[50];
    arc4random_buf(myRandomData, sizeof myRandomData);
    printf("%s", myRandomData);

    return 0;
}