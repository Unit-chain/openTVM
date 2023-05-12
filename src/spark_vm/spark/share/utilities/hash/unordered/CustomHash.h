//
// Created by Kirill Zhukov on 08.05.2023.
//

#ifndef VM_WITH_HEAP_CUSTOMHASH_H
#define VM_WITH_HEAP_CUSTOMHASH_H

#include "cstdio"
#include "string"
#include "wyhash.h"

class CustomHash {
public:
    size_t operator()(const std::string &s) const;
};

#endif //VM_WITH_HEAP_CUSTOMHASH_H
