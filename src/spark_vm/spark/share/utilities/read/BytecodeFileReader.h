//
// Created by Kirill Zhukov on 08.05.2023.
//

#ifndef VM_WITH_HEAP_BYTECODEFILEREADER_H
#define VM_WITH_HEAP_BYTECODEFILEREADER_H
#include "cstdio"
#include "string"
#include "hash/unordered/CustomHash.h"
#include "global/globalDefenitions.h"

#pragma pack(push, 1)

typedef struct {
    tuint32_t signature;
    tuint16_t disk_number;
    tuint16_t cd_disk_number;
    tuint16_t disk_entries;
    tuint16_t total_entries;
    tuint32_t cd_size;
    tuint32_t cd_offset;
    tuint16_t comment_length;
} EOCD;

typedef struct {
    uint32_t signature;
    uint16_t version_made_by;
    uint16_t version_needed;
    uint16_t flags;
    uint16_t compression;
    uint16_t mod_time;
    uint16_t mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
    uint16_t comment_length;
    uint16_t disk_number_start;
    uint16_t internal_file_attributes;
    uint32_t external_file_attributes;
    uint32_t local_header_offset;
} Central_directory_file_header;

#pragma pack(pop)

struct ProgramFile {
    unsigned long long offset;
    unsigned long long compressed_size;
};

enum BytecodeError : tuint16_t {
    ERR_FILE_OPEN       = 0x0001,
    ERR_BAD_EOCD        = 0x0002,
    ERR_BAD_EOCD_SIGN   = 0x0003,
    ERR_BAD_CD_SIGN     = 0x0004,
    ERR_BAD_FILENAME    = 0x0005,
    ERR_BAD_COMPRESSION = 0x0006,
    ERR_BAD_PROGRAM     = 0x0007
};

///@brief error processor
///@return 1 if execution should be stopped
typedef int (*bytecode_read_error_handler)(BytecodeError);

class BytecodeFileReader {
public:
    BytecodeFileReader() = delete;
    BytecodeFileReader(const char *path, bytecode_read_error_handler errorHandler);
public:
    bool err;
public:
    std::shared_ptr<char> getFiledata(const char* name);
private:
    EOCD eocd;
    const char *path;
    bytecode_read_error_handler errHandler;
    std::unordered_map<std::string, Central_directory_file_header, CustomHash> files;
private:
    void read_program();
};

#endif //VM_WITH_HEAP_BYTECODEFILEREADER_H
