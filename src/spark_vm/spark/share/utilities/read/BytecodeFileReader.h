//
// Created by Kirill Zhukov on 08.05.2023.
//

#ifndef VM_WITH_HEAP_BYTECODEFILEREADER_H
#define VM_WITH_HEAP_BYTECODEFILEREADER_H
#include "cstdio"
#include "string"
#include "hash/unordered/CustomHash.h"
#include "global/globalDefenitions.h"
#include "compression/zstd_decompression.h"

#pragma pack(push, 1)

typedef struct {
    uint32_t signature;
    uint16_t version;
    uint16_t flags;
    uint16_t compression;
    uint16_t mod_time;
    uint16_t mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
} Local_file_header;

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

typedef struct {
    Central_directory_file_header cd;
    Local_file_header lfh;
    std::shared_ptr<char> data;
} Compressed_file;

enum BytecodeError : tuint16_t {
    ERR_FILE_OPEN               = 0x0001,
    ERR_BAD_EOCD                = 0x0002,
    ERR_BAD_EOCD_SIGN           = 0x0003,
    ERR_BAD_CD_SIGN             = 0x0004,
    ERR_BAD_FILENAME            = 0x0005,
    ERR_BAD_COMPRESSION         = 0x0006,
    ERR_BAD_PROGRAM             = 0x0007,
    ERR_FILE_NOT_FOUND          = 0x0008,
    ERR_BAD_LOCAL_HEADER        = 0x0009,
    ERR_BAD_LOCAL_HEADER_SIGN   = 0x000A,
    ERR_READING_DATA            = 0x000B,
};

///@brief error processor
///@return returns 1 if execution should be stopped
typedef int (*bytecode_read_error_handler)(BytecodeError);

class BytecodeFileReader {
public:
    BytecodeFileReader() = delete;
    BytecodeFileReader(const char *path, bytecode_read_error_handler errorHandler);
public:
    bool err;
public:
    ///@brief get uncompressed data from program
    std::shared_ptr<char> getUncompressedProgram(const char *filename);
private:
    EOCD eocd;
    const char *path;
    bytecode_read_error_handler errHandler;
    std::unordered_map<std::string, Compressed_file, CustomHash> c_files;
#if 0
    std::unordered_map<std::string, Central_directory_file_header, CustomHash> files;
#endif
private:
    void read_program();
};

#endif //VM_WITH_HEAP_BYTECODEFILEREADER_H
