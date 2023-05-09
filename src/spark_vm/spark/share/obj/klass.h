//
// Created by Kirill Zhukov on 07.05.2023.
//

#ifndef VM_WITH_HEAP_KLASS_H
#define VM_WITH_HEAP_KLASS_H
#include "object_ref.h"

namespace theia {
    class klass : public theia::MetaObject {
    private:
        std::shared_ptr<klass> super;
        std::unique_ptr<method> methods;
    public:
        uintptr_t getSuperReference();
        std::shared_ptr<klass> getSuper();
    };
}
#endif //VM_WITH_HEAP_KLASS_H