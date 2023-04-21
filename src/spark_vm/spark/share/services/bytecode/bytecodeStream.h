//
// Created by Kirill Zhukov on 30.01.2023.
//

#ifndef VM_WITH_HEAP_BYTECODESTREAM_H
#define VM_WITH_HEAP_BYTECODESTREAM_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <boost/lexical_cast.hpp>
#include "global/globalDefenitions.h"


union unionData {
    cstring bytecode;
    bool error;
} fileData;

class bytecodeStream {
public:
    bytecodeStream() = default;
    virtual ~bytecodeStream();
    explicit bytecodeStream(FILE *fileDesc) : fptr(fileDesc){}
    short open(cstring *filePath);
    unionData readAll();
private:
    FILE *fptr = nullptr;
};


#endif //VM_WITH_HEAP_BYTECODESTREAM_H
