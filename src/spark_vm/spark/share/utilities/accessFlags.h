//
// Created by Kirill Zhukov on 13.01.2023.
//

#ifndef VM_WITH_HEAP_ACCESSFLAGS_H
#define VM_WITH_HEAP_ACCESSFLAGS_H
#include "global/globalDefenitions.h"

enum : u2 {
    ACC_PUBLIC = 0x0001,    // can be accessed outside package
    ACC_PRIVATE = 0x0002,
    ACC_SUPER = 0x0003,     // for parent class methods
    ACC_PROTECTED = 0x0004,
    ACC_ATTRIBUTE = 0x0007, // attribute
    ACC_STATIC = 0x0008,    // static function
    ACC_FINAL = 0x0011,     // can't be changed
    ACC_NATIVE = 0x0100,    // native function
    ACC_INTERFACE = 0x0200, // interface
    ACC_ABSTRACT = 0x0400,  // shouldn't have instance classes
    ACC_ENUM = 0x4000       // enum
};

class AccessFlags {
public:
    AccessFlags();
    explicit AccessFlags(tint flags);

    [[nodiscard]] bool isPublic() const;
    [[nodiscard]] bool isPrivate() const;
    [[nodiscard]] bool isSuper() const;
    [[nodiscard]] bool isProtected() const;
    [[nodiscard]] bool isAttribute() const;
    [[nodiscard]] bool isStatic() const;
    [[nodiscard]] bool isFinal() const;
    [[nodiscard]] bool isNative() const;
    [[nodiscard]] bool isAbstract() const;
    [[nodiscard]] bool isInterface() const;
    [[nodiscard]] bool isEnum() const;

    [[nodiscard]] tint getFlags() const;
    void setFlags(tint flags);
private:
    tint _flags;
};

#endif //VM_WITH_HEAP_ACCESSFLAGS_H