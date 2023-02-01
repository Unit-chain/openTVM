//
// Created by Kirill Zhukov on 01.02.2023.
//

#ifndef VM_WITH_HEAP_METHODCOUNTERS_H
#define VM_WITH_HEAP_METHODCOUNTERS_H
#include "atomic"
#include "services/memory/metaObject.h"
#include "global/globalDefenitions.h"

/// @class MethodCounters
/// @brief class for counting actions with method
/// @var MethodCounters::invocationCounter used for counting invocation times
/// @var MethodCounters::optimizationLevel used for storing info about optimization level
class MethodCounters : public metaObject {
public:
    void increase();
private:
    tint invocationCounter = 0;
    u1 optimizationLevel = 0;
};


#endif //VM_WITH_HEAP_METHODCOUNTERS_H
