//
// Created by Kirill Zhukov on 07.05.2023.
//

#include "klass.h"

uintptr_t theia::klass::getSuperReference() {
    return (uintptr_t) this->super.get();
}

std::shared_ptr<theia::klass> theia::klass::getSuper() {
    return this->super;
}
