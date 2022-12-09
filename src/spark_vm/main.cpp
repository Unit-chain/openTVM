#include <iostream>
#include <cstdlib>
#include <array>
#include "hash/MurmurHash3.h"
#include "hash/xxhash.h"

#define BUFFSIZE 128

//size_t XXH32_wrapper(const void* src, size_t srcSize, void* dst, size_t dstCapacity, void* customPayload) {
//    (void)dst; (void)dstCapacity; (void)customPayload;
//    return (size_t) XXH32(src, srcSize, 0);
//}
size_t XXH32_wrapper(const void* src, size_t srcSize) {
    return (size_t) XXH32(src, srcSize, 0);
}

int main(int argc, char* argv[]) {
    std::string str = "abc";
    XXH64_hash_t hash = XXH64(str.data(), str.size(), 0);
    std::cout << hash << std::endl;
    std::array<uint64_t, 2> hashValue{};
    MurmurHash3_x64_128(str.data(), str.size(), 0, hashValue.data());
    std::cout << "hash: ";
    for (auto it : hashValue) {
        std::cout << it;
    }
    std::cout << std::endl;
    XXH128_hash_t hash1 = XXH3_128bits(str.data(), str.size());
    std::cout << "xxhash128: " << hash1.high64 << hash1.low64 << std::endl;

//    char buff[128];
//
//    uint32_t u32;
//    uint64_t u64;
//
//    int seed = 0;
//    strcpy(buff, str.c_str());
//
//    if (argc >= 2) {
//        if (strlen(argv[1]) > BUFFSIZE - 1) return(0);
//        strcpy(buff, argv[1]);
//    }
//    if (argc >= 3) seed = atoi(argv[2]);
//
//    printf("String: %s\n", buff);
//    printf("Seed: %d\n\n", seed);
//
//
//    puts("\n===xxHash===");
//    XXH32_hash_t u32x = XXH32(buff, strlen(buff), (XXH32_hash_t)0);
//    printf("xx3Hash32\t\t\t%u Hex: %x\n", u32x, u32x);
//    u32x = XXH32(buff, strlen(buff), (XXH32_hash_t)seed);
//    printf("xx3Hash32+Seed\t\t\t%u Hex: %x\n", u32x, u32x);

//    XXH64_hash_t u64x = XXH64(buff, strlen(buff), (XXH64_hash_t)0);
//    printf("xx3Hash64\t\t\t%lld Hex: %llx\n", u64x, u64x);
//    u64x = XXH64(buff, strlen(buff), (XXH64_hash_t)seed);
//    printf("xx3Hash64+Seed\t\t\t%llu Hex: %llx\n", u64x, u64x);
//
//    XXH128_hash_t u128x = XXH128(buff, strlen(buff), (XXH64_hash_t)0);
//    printf("xx3Hash128\t\t\t%llx%llx\n", u128x.high64, u128x.low64);
//
//
//    u128x = XXH128(buff, strlen(buff), (XXH64_hash_t)seed);
//    printf("xx3Hash128+Seed\t\t\t%llx%llx\n", u128x.high64, u128x.low64);
//#ifdef _LP64
//    std::cout << 111 << std::endl;
//#endif




//    __linux__       Defined on Linux
//    __sun           Defined on Solaris
//    __FreeBSD__     Defined on FreeBSD
//    __NetBSD__      Defined on NetBSD
//    __OpenBSD__     Defined on OpenBSD
//    __APPLE__       Defined on Mac OS X
//    __hpux          Defined on HP-UX
//    __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
//    __sgi           Defined on Irix
//    _AIX            Defined on AIX
//    _WIN32          Defined on Windows
//
//    #ifdef __linux__
//        std::cout << "linux" << std::endl;
//    #elif _WIN32
//        std::cout << "windows" << std::endl;
//    #elif __APPLE__
//        std::cout << "macos" << std::endl;
//    #endif

    return 0;
}
