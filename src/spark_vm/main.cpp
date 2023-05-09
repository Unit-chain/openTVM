#include "iostream"
#include "memory"
#include "compression/zstd_decompression.h"
#include "hash/unordered/CustomHash.h"
#include "read/BytecodeFileReader.h"

int main() {
//    std::shared_ptr<char> uncompressed_data = getAllDataFromCompressedFile("/Users/kirillzhukov/Desktop/pitch_speech.md.zst");
//    std::shared_ptr<char> uncompressed_data = getDataFromCompressedFile("/Users/kirillzhukov/Desktop/pitch_speech.md.zst", 0, 3237);
//    printf("data:\n%s\n", uncompressed_data.get());
    printf("size: %zu\n", sizeof(Central_directory_file_header));
    return 0;
}