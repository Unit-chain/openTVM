//
// Created by Kirill Zhukov on 08.05.2023.
//

#include "BytecodeFileReader.h"

BytecodeFileReader::BytecodeFileReader(const char *path, bytecode_read_error_handler errorHandler) {
    this->errHandler = errorHandler;
    this->path = path;
}

std::shared_ptr<char> BytecodeFileReader::program(char *fileName, char *package) {
    FILE *fp;
    fp = fopen(path, "rb");
    if (fp == NULL)
        this->errHandler(ERR_FILE_OPEN);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned long long EOCD_offset = size - 22;
}
