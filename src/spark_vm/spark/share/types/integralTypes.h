//
// Created by Kirill Zhukov on 02.02.2023.
//

#ifndef VM_WITH_HEAP_INTEGRALTYPES_H
#define VM_WITH_HEAP_INTEGRALTYPES_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cinttypes>

#ifdef __SIZEOF_INT128__
typedef __uint128_t uint128_t;
#elif

#endif

//uint32_t a,b;
//uint64_t c = UINT64_MAX;
//
//a = (uint32_t)((c & 0xFFFFFFFF00000000LL) >> 32);
//b = (uint32_t)(c & 0xFFFFFFFFLL);
//std::cout << "a = " << a << std::endl << "b = " << b << std::endl << "c = " << (((uint64_t)a) << 32 | b) << std::endl;

#define UINT128_C(u)     ((__uint128_t)u)
const __uint128_t UINT128_MAX = UINT128_C(UINT64_MAX)<<64 | UINT64_MAX;
void pu64(__uint64_t u)   { printf("%" PRIu64, u); }
void pu640(__uint64_t u)  { printf("%019" PRIu64, u); }

#define D19_ UINT64_C(10000000000000000000)
const __uint128_t d19_ = D19_;
const __uint128_t d38_ = UINT128_C(D19_)*D19_;


void pu128(__uint128_t u)
{
    if (u < d19_) pu64(u);
    else if (u < d38_) { pu64(u/d19_); pu640(u%d19_); }
    else               { pu64(u/d38_); u%=d38_; pu640(u/d19_); pu640(u%d19_); }
}

/// @brief used for converting char to unsigned types
/// @param ch char to be converted into integer
signed short strtou_t(char ch) {
    return (ch >= '0' && ch <= '9') ? ch - '0'
                                 :  (ch >= 'a' && ch <= 'z') ? ch - 'a' + 10
                                                           :  (ch >= 'A' && ch <= 'Z') ? ch - 'A' + 10
                                                                                     :  255;
}

/// @brief used for translating strings into uint128_t
uint128_t stou128_t(const char *str, unsigned char base = 10) {
    if (*str == '0') {
        if (str[1] == 'X' || str[1] == 'x') goto nonbinary;
        if (str[1] == 'B' || str[1] == 'b') goto binary;
        goto nonbinary;
    }
    goto nonbinary;
    binary: {
        uint128_t value;
        size_t strLength = strlen(str);
        for(size_t i = 2; i < strLength; ++i) {
            value = (value << 1 | strtou_t(str[i]));
        }
        return value;
    };

    nonbinary: {
        int digit;
        uint128_t value;
        while ((digit = strtou_t(*str)) < base) {
            uint128_t v0 = value;
            value = value * base + digit;
                if (value < v0) {
                    value = ~(uint128_t) 0;
                }
            ++str;
        }
        return value;
    };
}

__uint128_t set_128(uint64_t h, uint64_t l) {
    __uint128_t r = h;
    return (r << 64) + l;
}

typedef __uint128_t uint256_t[2];

void set_256(uint256_t d, __uint128_t l, __uint128_t h)  {
    d[0] = l;
    d[1] = h;
}
#endif //VM_WITH_HEAP_INTEGRALTYPES_H
