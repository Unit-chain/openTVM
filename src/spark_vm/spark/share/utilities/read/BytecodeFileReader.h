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
#include "zip.h"

class BytecodeFileReader {
public:
    explicit BytecodeFileReader(std::string &path);
public:
    bool err{};
public:
    ///@brief get uncompressed data from program
    std::shared_ptr<char> getUncompressedProgram(const std::string& filename);
    [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<char>, CustomHash> &getFiles() const;

private:
    std::string path;
    std::unordered_map<std::string, std::shared_ptr<char>, CustomHash> files;
private:
    void read_program();
};

#endif //VM_WITH_HEAP_BYTECODEFILEREADER_H
