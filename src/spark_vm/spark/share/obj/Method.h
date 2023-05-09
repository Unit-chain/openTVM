//
// Created by Kirill Zhukov on 07.05.2023.
//

#ifndef VM_WITH_HEAP_METHOD_H
#define VM_WITH_HEAP_METHOD_H
#include "object_ref.h"
#include "klass.h"

namespace theia {
    ///@param owner null if method is outside class
    class method : public theia::MetaObject {
    public:
        std::unique_ptr<klass> owner;
    private:
        u1 *code;
    public:
        void loadCode(FILE *fptr, int offset);
    };
}

#endif //VM_WITH_HEAP_METHOD_H
