//
// Created by Kirill Zhukov on 08.05.2023.
//

#include "BytecodeFileReader.h"

BytecodeFileReader::BytecodeFileReader(const char *path, bytecode_read_error_handler errorHandler) {
    this->errHandler = errorHandler;
    this->path = path;
}

void BytecodeFileReader::read_program() {
    FILE *fp;
    fp = fopen(path, "rb");
    if (fp == NULL) {
        this->errHandler(ERR_FILE_OPEN);
    }
    fseek(fp, 0, SEEK_END);
    tlong_t size = ftell(fp);
    tlong_t EOCD_offset = size - 22;
    fseek(fp, EOCD_offset, SEEK_SET);
    if (fread(&(this->eocd), sizeof(EOCD), 1, fp) != 1) {
        this->errHandler(ERR_READ_EOCD);
    }
    if (ntohl(htonl(this->eocd.signature)) != 0x06054b50) {
        this->errHandler(ERR_BAD_EOCD_SIGN);
    }
    fseek(fp, this->eocd.cd_offset, SEEK_SET);
    for (tuint16_t i = 0; i < this->eocd.total_entries; ++i) {
        Central_directory_file_header cd;
        if (fread(&cd, sizeof(Central_directory_file_header), 1, fp) != 1) {
            this->errHandler(ERR_READ_EOCD);
        }
        cd.signature = ntohl(htonl(cd.signature));
        if (cd.signature != 0x02014b50) {
            this->errHandler(ERR_BAD_CD_SIGN);
        }
        char filename[cd.filename_length];
        if (fread(&filename, cd.filename_length, 1, fp) != 1) {
            this->errHandler(ERR_BAD_FILENAME);
        }
        fseek(fp, cd.extra_field_length, SEEK_CUR);
        this->files.insert_or_assign(std::string(filename), std::move(cd));
    }
}