//
// Created by Kirill Zhukov on 01.02.2023.
//

#ifndef VM_WITH_HEAP_METHODDATA_H
#define VM_WITH_HEAP_METHODDATA_H
#include "mutex"
#include "Method.h"


class MethodData : public metaObject {
public:
    MethodData(cstring *code, const Method &backMethod);
private:
    /// pointer to method
    cstring _code;
    Method _backMethod;
    uLock *mutex{};
};


#endif //VM_WITH_HEAP_METHODDATA_H
