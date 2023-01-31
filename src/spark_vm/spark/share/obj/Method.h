//
// Created by Kirill Zhukov on 31.01.2023.
//

#ifndef VM_WITH_HEAP_METHOD_H
#define VM_WITH_HEAP_METHOD_H
#include "Symbol.h"
#include "utilities/accessFlags.h"

class Method {
public:
    volatile Symbol* name;
private:
    AccessFlags _accessFlags;
};


#endif //VM_WITH_HEAP_METHOD_H
