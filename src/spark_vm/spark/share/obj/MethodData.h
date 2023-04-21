//
// Created by Kirill Zhukov on 01.02.2023.
//

#ifndef VM_WITH_HEAP_METHODDATA_H
#define VM_WITH_HEAP_METHODDATA_H
#include "mutex"
#include "memory/metaObject.h"
#include "utilities/Lock.h"
#include "global/globalDefenitions.h"
#include "Method.h"

class MethodData : public metaObject {
public:
    MethodData(cstring *code, Method *method);
private:
    cstring _code;
    /// pointer to method
    Method *_backMethod;
    uLock *mutex{};
};


#endif //VM_WITH_HEAP_METHODDATA_H
