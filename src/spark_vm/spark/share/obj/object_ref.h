//
// Created by Kirill Zhukov on 07.05.2023.
//

#ifndef VM_WITH_HEAP_OBJECT_REF_H
#define VM_WITH_HEAP_OBJECT_REF_H
#include "memory"
#include "cstdio"
#include "accessFlags.h"

namespace theia {
    class klass;
    class method;

    class MetaObject {
    public:
        MetaObject();
        MetaObject(tint flags, char *name);
    public:
        AccessFlags flags;
        char* name;
    public:
        virtual void loadName() = 0;
    };
}
#endif //VM_WITH_HEAP_OBJECT_REF_H
