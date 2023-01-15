//
// Created by Kirill Zhukov on 13.01.2023.
//

#ifndef VM_WITH_HEAP_ACCESSFLAGS_H
#define VM_WITH_HEAP_ACCESSFLAGS_H

enum {
    ACC_PUBLIC = 0x0001,    // can be accessed outside package
    ACC_PRIVATE = 0x0010,
    ACC_PROTECTED = 0x0011,
    ACC_STATIC = 0x0012,
    ACC_NATIVE = 0x0013,
    ACC_VOLATILE = 0x0014,
    ACC_FINAL = 0x0002,     // no subclasses
    ACC_SUPER = 0x0003,     // for parent class methods
    ACC_INTERFACE = 0x0004, // interface
    ACC_ABSTRACT = 0x0005,  // should have instance classes
    ACC_ENUM = 0x0006,      // enum
    ACC_ATTRIBUTE = 0x0007  // attribute
};

#endif //VM_WITH_HEAP_ACCESSFLAGS_H
