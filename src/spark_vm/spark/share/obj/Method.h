//
// Created by Kirill Zhukov on 31.01.2023.
//

#ifndef VM_WITH_HEAP_METHOD_H
#define VM_WITH_HEAP_METHOD_H
#include "Symbol.h"
#include "MethodData.h"
#include "MethodCounters.h"
#include "utilities/Lock.h"
#include "utilities/accessFlags.h"

class MethodData;

class Method : public metaObject {
public:
    volatile Symbol* name;
private:
    AccessFlags _accessFlags;
    int vTableIndex;
    MethodData *_data;
    MethodCounters *_counters;
};


#endif //VM_WITH_HEAP_METHOD_H
