//
// Created by Kirill Zhukov on 03.02.2023.
//

#ifndef VM_WITH_HEAP_COMPILEDCODE_H
#define VM_WITH_HEAP_COMPILEDCODE_H
#include "global/globalDefenitions.h"
#include "jemalloc/jemalloc.h"

template<unsigned int S>
class CompiledNativeCode {
public:
    explicit CompiledNativeCode(instruction *program) : program(program) {}
    inline void allocateMemory();
private:
    instruction program[S];
};

#endif //VM_WITH_HEAP_COMPILEDCODE_H
