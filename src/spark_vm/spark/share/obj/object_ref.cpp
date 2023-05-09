//
// Created by Kirill Zhukov on 07.05.2023.
//

#include "object_ref.h"

theia::MetaObject::MetaObject() {
    this->flags.setFlags(ACC_PUBLIC);
}

theia::MetaObject::MetaObject(tint_t flags, char *name) : flags(flags) {
    this->name = name;
}