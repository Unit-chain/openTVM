//
// Created by Kirill Zhukov on 08.05.2023.
//

#include "zstd_decompression.h"

filebuff *readFile(const std::string &path) {
    FILE *fp;
    fp = fopen(path.c_str(), "rb");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // counting size
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buff = (char *) malloc(size);
    fread(buff, sizeof(char), size, (FILE *) fp);
    filebuff *fb = (filebuff *) malloc(sizeof(filebuff));
    fb->buff = buff;
    fb->size = size;
    fclose(fp);
    return fb;
}

std::shared_ptr<char> getAllDataFromCompressedFile(char *path) {
    filebuff *fb = readFile(path);
    size_t compressed_size = fb->size;
    void *compressed_data = (void *) fb->buff;
    // determine the size of the decompressed data
    size_t uncompressed_size = ZSTD_getFrameContentSize(compressed_data, compressed_size);
    printf("uncompressed size: %zu, compressed size: %zu\n", uncompressed_size, compressed_size);
    // allocate a buffer to hold the decompressed data
    void *uncompressed_data = malloc(uncompressed_size);
    // decompress the data
    size_t actual_uncompressed_size = ZSTD_decompress(uncompressed_data, uncompressed_size, compressed_data,
                                                      compressed_size);
    // do something with the decompressed data
    // clean up
    free(fb->buff);
    free(fb);
    return std::shared_ptr<char>((char *) uncompressed_data);
}

std::shared_ptr<char> getDataFromCompressedFile(char *path, size_t offset, size_t compressed_data_size) {
    FILE *fp;
    fp = fopen(path, "rb");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    fseek(fp, offset, SEEK_SET);
    char compressed_data[compressed_data_size];
    fread(compressed_data, sizeof(char), compressed_data_size, (FILE *) fp);
    size_t uncompressed_size = ZSTD_getFrameContentSize(compressed_data, compressed_data_size);
    void* uncompressed_data = malloc(uncompressed_size);
    size_t actual_uncompressed_size = ZSTD_decompress(uncompressed_data, uncompressed_size, compressed_data,
                                                      compressed_data_size);
    fclose(fp);
    return std::shared_ptr<char>((char *)uncompressed_data);
}