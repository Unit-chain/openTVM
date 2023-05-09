//
// Created by Kirill Zhukov on 08.05.2023.
//

#ifndef VM_WITH_HEAP_CUSTOMHASH_H
#define VM_WITH_HEAP_CUSTOMHASH_H

#include "cstdio"
#include "string"
#include "th_hash.h"

static const unsigned seeds[12] = {
        0x7fe96c80, 0x6e11ce04, 0x71bb7d87, 0xd7275b5e,
        0x321aaed9, 0xb318bd6b, 0x385f5156, 0x208cc10f,
        0x97733625, 0x7ae1991d, 0x0e866525, 0xc5cdcb89
};

static uint16_t seed_round = 0;
#define MAP_MODULO 2048

class CustomHash {
public:
    size_t operator()(const std::string &s) const;
    size_t operator()(unsigned long long k) const;
};

#endif //VM_WITH_HEAP_CUSTOMHASH_H
