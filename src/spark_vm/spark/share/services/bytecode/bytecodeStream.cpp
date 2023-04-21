//
// Created by Kirill Zhukov on 30.01.2023.
//

#include "bytecodeStream.h"
#include "jemalloc/jemalloc.h"
#include "logger/logger.h"

short bytecodeStream::open(cstring *filePath) {
    size_t pathLen = strlen(*filePath);
    auto path = static_cast<cstring>(malloc(pathLen));
    strlcpy(path, *filePath, pathLen);
    this->fptr = fopen((char*) filePath, "r");

    if (this->fptr == nullptr) return -1;
    free(path);
    return 1;
}

bytecodeStream::~bytecodeStream() {
    if (this->fptr != nullptr)
        fclose(this->fptr);
}

unionData bytecodeStream::readAll() {
    char *size = nullptr;
    size_t len = 0;
    size_t read;
    if (getline(&size, &len, this->fptr) == -1) {
        return fileData = {.error = true};
    }
    size_t fileSize;
    try {
        fileSize = std::stoi(size);
    } catch (std::invalid_argument &e) {
        logging(e.what(), LoggingLevel::ERROR, stdout);
        return fileData = {.error = true };
    }
    char buff[fileSize];
    fread(buff, sizeof(char), fileSize, (FILE*)this->fptr);
    fclose(this->fptr);
    return fileData = {.bytecode = buff};
}
