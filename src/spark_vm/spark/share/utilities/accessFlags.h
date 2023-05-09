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
    explicit AccessFlags(tint_t flags);

    [[nodiscard]] tboolean_t isPublic() const;
    [[nodiscard]] tboolean_t isPrivate() const;
    [[nodiscard]] tboolean_t isSuper() const;
    [[nodiscard]] tboolean_t isProtected() const;
    [[nodiscard]] tboolean_t isAttribute() const;
    [[nodiscard]] tboolean_t isStatic() const;
    [[nodiscard]] tboolean_t isFinal() const;
    [[nodiscard]] tboolean_t isNative() const;
    [[nodiscard]] tboolean_t isAbstract() const;
    [[nodiscard]] tboolean_t isInterface() const;
    [[nodiscard]] tboolean_t isEnum() const;
    [[nodiscard]] tboolean_t isPrivateOrProtected() const;

    [[nodiscard]] tint_t getFlags() const;
    void setFlags(tint_t flags);
private:
    tint_t flags;
};

#endif //VM_WITH_HEAP_ACCESSFLAGS_H