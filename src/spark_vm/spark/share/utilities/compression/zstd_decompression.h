//
// Created by Kirill Zhukov on 08.05.2023.
//

#ifndef VM_WITH_HEAP_ZSTD_DECOMPRESSION_H
#define VM_WITH_HEAP_ZSTD_DECOMPRESSION_H
#include "memory"
#include "string"
#include "zstd.h"

struct filebuff {
    long size;
    char *buff;
};

filebuff *readFile(const std::string& path);
std::shared_ptr<char> getAllDataFromCompressedFile(char *path);
std::shared_ptr<char> getDataFromCompressedFile(char *path, size_t offset, size_t compressed_data_size);

#endif //VM_WITH_HEAP_ZSTD_DECOMPRESSION_H
