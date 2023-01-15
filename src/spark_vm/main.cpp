#include <iostream>
#include <cstdio>
#include <sys/mman.h>
#include "logger/loggerTime.h"
#include "logger/logger.h"
#include "iostream"
#include "sstream"
#include "spark/memory/alloc.h"

#define print(x) puts(#x)
#define concat(x, y) print(x##y)

#define MEMORY_TYPES_DO(f)                                                           \
  /* Memory type by sub systems. It occupies lower byte. */                          \
  f(mtJavaHeap,       "Java Heap")   /* Java heap                                 */ \

void test(const std::string& str) {
    puts(str.c_str());
}

struct btest {
    bool a = true;
    bool b = true;
    bool c = true;
    bool d = true;
    bool e = true;
    bool f = true;
    bool g = true;
    bool h = true;
};

int main() {
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

#if 1
    int a = 10;
    auto p = (uintptr_t) &a;
    auto pt = (long) &a;
    std::cout << &a << std::endl;
    std::cout << p << std::endl;
    std::cout << *reinterpret_cast<int*>(p) << std::endl;

    std::cout << pt << std::endl;
    std::cout << *reinterpret_cast<int*>(pt) << std::endl;
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

    return 0;
}