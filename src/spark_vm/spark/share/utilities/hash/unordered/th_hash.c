//
// Created by Kirill Zhukov on 08.05.2023.
//
#include "th_hash.h"

unsigned _wyr32(const uint8_t *p) {
    unsigned v;
    memcpy(&v, p, 4);
    return v;
}

unsigned _wyr24(const uint8_t *p, unsigned k) {
    return (((unsigned) p[0]) << 16) | (((unsigned) p[k >> 1]) << 8) | p[k - 1];
}

void _wymix32(unsigned *A, unsigned *B) {
    uint64_t c = *A ^ 0x53c5ca59u;
    c *= *B ^ 0x74743c1bu;
    *A = (unsigned) c;
    *B = (unsigned) (c >> 32);
}

unsigned wyhash32(const void *key, uint64_t len, unsigned seed) {
    const uint8_t *p = (const uint8_t *) key;
    uint64_t i = len;
    unsigned see1 = (unsigned) len;
    seed ^= (unsigned) (len >> 32);
    _wymix32(&seed, &see1);
    for (; i > 8; i -= 8, p += 8) {
        seed ^= _wyr32(p);
        see1 ^= _wyr32(p + 4);
        _wymix32(&seed, &see1);
    }
    if (i >= 4) {
        seed ^= _wyr32(p);
        see1 ^= _wyr32(p + i - 4);
    } else if (i)
        seed ^= _wyr24(p, (unsigned) i);
    _wymix32(&seed, &see1);
    _wymix32(&seed, &see1);
    return seed ^ see1;
}