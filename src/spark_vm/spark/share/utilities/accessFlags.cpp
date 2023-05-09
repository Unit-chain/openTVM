//
// Created by Kirill Zhukov on 31.01.2023.
//

#include "accessFlags.h"

bool AccessFlags::isPublic() const {
    return (this->flags & ACC_PUBLIC) != 0;
}

bool AccessFlags::isPrivate() const {
    return (this->flags & ACC_PRIVATE) != 0;
}

bool AccessFlags::isSuper() const {
    return (this->flags & ACC_SUPER) != 0;
}

bool AccessFlags::isProtected() const {
    return (this->flags & ACC_PROTECTED) != 0;
}

bool AccessFlags::isAttribute() const {
    return (this->flags & ACC_ATTRIBUTE) != 0;
}

bool AccessFlags::isStatic() const {
    return (this->flags & ACC_STATIC) != 0;
}

bool AccessFlags::isFinal() const {
    return (this->flags & ACC_FINAL) != 0;
}

bool AccessFlags::isNative() const {
    return (this->flags & ACC_NATIVE) != 0;
}

bool AccessFlags::isAbstract() const {
    return (this->flags & ACC_ABSTRACT) != 0;
}

bool AccessFlags::isInterface() const {
    return (this->flags & ACC_INTERFACE) != 0;
}

bool AccessFlags::isEnum() const {
    return (this->flags & ACC_ENUM) != 0;
}

tint_t AccessFlags::getFlags() const {
    return flags;
}

void AccessFlags::setFlags(tint_t flags) {
    flags = flags;
}

AccessFlags::AccessFlags(tint_t flags) : flags(flags) {}

AccessFlags::AccessFlags() : flags(0) {}

bool AccessFlags::isPrivateOrProtected() const {
    return (this->isPrivate()) || (this->isProtected());
}
