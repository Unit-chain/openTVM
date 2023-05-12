#include "iostream"
#include "memory"
#include "compression/zstd_decompression.h"
#include "hash/unordered/CustomHash.h"
#include "read/BytecodeFileReader.h"

int main() {
    BytecodeFileReader bytecodeFileReader("/Users/kirillzhukov/Desktop/ar/cpp.zip");
    std::cout << "value: " << '\n' << bytecodeFileReader.getUncompressedProgram("p2p/CMakeLists.txt").get() << '\n';
    return 0;
}