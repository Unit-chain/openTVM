//
// Created by Kirill Zhukov on 31.01.2023.
//

#include "accessFlags.h"

bool AccessFlags::isPublic() const {
    return (this->_flags & ACC_PUBLIC) != 0;
}

bool AccessFlags::isPrivate() const {
    return (this->_flags & ACC_PRIVATE) != 0;
}

bool AccessFlags::isSuper() const {
    return (this->_flags & ACC_SUPER) != 0;
}

bool AccessFlags::isProtected() const {
    return (this->_flags & ACC_PROTECTED) != 0;
}

bool AccessFlags::isAttribute() const {
    return (this->_flags & ACC_ATTRIBUTE) != 0;
}

bool AccessFlags::isStatic() const {
    return (this->_flags & ACC_STATIC) != 0;
}

bool AccessFlags::isFinal() const {
    return (this->_flags & ACC_FINAL) != 0;
}

bool AccessFlags::isNative() const {
    return (this->_flags & ACC_NATIVE) != 0;
}

bool AccessFlags::isAbstract() const {
    return (this->_flags & ACC_ABSTRACT) != 0;
}

bool AccessFlags::isInterface() const {
    return (this->_flags & ACC_INTERFACE) != 0;
}

bool AccessFlags::isEnum() const {
    return (this->_flags & ACC_ENUM) != 0;
}

tint AccessFlags::getFlags() const {
    return _flags;
}

void AccessFlags::setFlags(tint flags) {
    _flags = flags;
}

AccessFlags::AccessFlags(tint flags) : _flags(flags) {}

AccessFlags::AccessFlags() : _flags(0) {}