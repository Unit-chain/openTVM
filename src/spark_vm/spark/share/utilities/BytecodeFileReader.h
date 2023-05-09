//
// Created by Kirill Zhukov on 08.05.2023.
//

#ifndef VM_WITH_HEAP_BYTECODEFILEREADER_H
#define VM_WITH_HEAP_BYTECODEFILEREADER_H
#include "cstdio"
#include "string"
#include "hash/unordered/CustomHash.h"

#pragma pack(push, 1)

struct EOCD {
    uint32_t signature;
    uint16_t disk_number;
    uint16_t cd_disk_number;
    uint16_t disk_entries;
    uint16_t total_entries;
    uint32_t cd_size;
    uint32_t cd_offset;
    uint16_t comment_length;
};

#pragma pack(pop)

struct ProgramFile {
    unsigned long long offset;
    unsigned long long compressed_size;
};

enum BytecodeError : uint16_t {
    ERR_FILE_OPEN = 0x0001
};

typedef void (*bytecode_read_error_handler)(BytecodeError);

class BytecodeFileReader {
public:
    BytecodeFileReader() = delete;
    BytecodeFileReader(const char *path, bytecode_read_error_handler errorHandler);
    std::shared_ptr<char> program(char *fileName, char *package);
private:
    const char *path;
    bytecode_read_error_handler errHandler;
    std::unordered_map<unsigned long long, ProgramFile, CustomHash> files;
};

#endif //VM_WITH_HEAP_BYTECODEFILEREADER_H
