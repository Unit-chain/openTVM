//
// Created by Kirill Zhukov on 31.01.2023.
//

#ifndef VM_WITH_HEAP_METHOD_H
#define VM_WITH_HEAP_METHOD_H
#include "Symbol.h"
#include "MethodCounters.h"
#include "utilities/Lock.h"
#include "utilities/accessFlags.h"

class MethodData;

class Method : public metaObject {
public:
    Method();
    volatile Symbol* name;
private:
    MethodData *_data;
    AccessFlags _accessFlags;
    MethodCounters *_counters;
    int vTableIndex;
};


#endif //VM_WITH_HEAP_METHOD_H
