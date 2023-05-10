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
    fp = fopen(this->path, "rb");
    if (fp == NULL) {
        if(this->errHandler(ERR_FILE_OPEN) == 1) {
            this->err = true;
            return;
        }
    }
    fseek(fp, 0, SEEK_END);
    tlong_t size = ftell(fp);
    tlong_t EOCD_offset = size - 22;
    fseek(fp, EOCD_offset, SEEK_SET);
    if (fread(&(this->eocd), sizeof(EOCD), 1, fp) != 1) {
        if(this->errHandler(ERR_BAD_EOCD) == 1) {
            this->err = true;
            return;
        }
    }
    if (ntohl(htonl(this->eocd.signature)) != 0x06054b50) {
        if(this->errHandler(ERR_BAD_EOCD_SIGN) == 1) {
            this->err = true;
            return;
        }
    }
    fseek(fp, this->eocd.cd_offset, SEEK_SET);
    for (tuint16_t i = 0; i < this->eocd.total_entries; ++i) {
        Central_directory_file_header cd;
        if (fread(&cd, sizeof(Central_directory_file_header), 1, fp) != 1) {
            if(this->errHandler(ERR_BAD_EOCD) == 1) {
                this->err = true;
                return;
            }
        }
        cd.signature = ntohl(htonl(cd.signature));
        if (cd.signature != 0x02014b50) {
            if(this->errHandler(ERR_BAD_CD_SIGN) == 1) {
                this->err = true;
                return;
            }
        }
        // Zstandard (zstd) compression flag according to: 4.4.5(https://pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT)
        if (cd.compression != 0x5D) {
            if(this->errHandler(ERR_BAD_COMPRESSION) == 1) {
                this->err = true;
                return;
            }
        }
        char filename[cd.filename_length];
        if (fread(&filename, cd.filename_length, 1, fp) != 1) {
            if(this->errHandler(ERR_BAD_FILENAME) == 1) {
                this->err = true;
                return;
            }
        }
        fseek(fp, cd.extra_field_length, SEEK_CUR);
        tuint64_t old_pos = ftell(fp);
        fseek(fp, cd.local_header_offset, SEEK_SET);

        Local_file_header lfh;
        if (fread(&lfh, sizeof(Local_file_header), 1, fp) != 1) {
            if(this->errHandler(ERR_READING_DATA) == 1) {
                this->err = true;
                return;
            }
        }
        lfh.signature = ntohl(htonl(lfh.signature));
        if (cd.signature != 0x02014b50) {
            if(this->errHandler(ERR_BAD_LOCAL_HEADER_SIGN) == 1) {
                this->err = true;
                return;
            }
        }
        char data[lfh.compressed_size];
        if (fread(&data, lfh.compressed_size, 1, fp) != 1) {
            if(this->errHandler(ERR_READING_DATA) == 1) {
                this->err = true;
                return;
            }
        }
        Compressed_file cf =  {cd, lfh, getUncompressedData(data, lfh.compressed_size)};
        this->c_files.insert_or_assign(filename, cf);
#if 0
        this->files.insert_or_assign(std::string(filename), std::move(cd));
#endif
    }
#if !(BLOCKCHAIN_USAGE)
    if (!this->c_files.contains("metadata.properties")) {
        this->errHandler(ERR_BAD_PROGRAM);
        exit(1);
    }
#endif
}

#if 0
std::shared_ptr<char> BytecodeFileReader::getFileData(const char *name) {
    std::string filename(name);
    if (!this->files.contains(filename)) {
        if(this->errHandler(ERR_FILE_NOT_FOUND) == 1) {
            this->err = true;
            return nullptr;
        }
    }
    Central_directory_file_header cd = this->files.at(filename);

    FILE *fp;
    fp = fopen(this->path, "rb");
    if (fp == NULL) {
        if(this->errHandler(ERR_FILE_OPEN) == 1) {
            this->err = true;
            return nullptr;
        }
    }
    fseek(fp, cd.local_header_offset, SEEK_SET);
    Local_file_header lfh;
    if (fread(&lfh, sizeof(lfh), 1, fp) != 1) {
        if(this->errHandler(ERR_BAD_LOCAL_HEADER) == 1) {
            this->err = true;
            return nullptr;
        }
    }
    lfh.signature = ntohl(htonl(lfh.signature));
    if (cd.signature != 0x02014b50) {
        if(this->errHandler(ERR_BAD_LOCAL_HEADER_SIGN) == 1) {
            this->err = true;
            return nullptr;
        }
    }
    char data[lfh.compressed_size];
    if (fread(&data, lfh.compressed_size, 1, fp) != 1) {
        if(this->errHandler(ERR_READING_DATA) == 1) {
            this->err = true;
            return nullptr;
        }
    }
    return getUncompressedData(data, lfh.compressed_size);
}
#endif

std::shared_ptr<char> BytecodeFileReader::getUncompressedProgram(const char *filename) {
    if (!this->c_files.contains(filename)) {
        return nullptr;
    }
    Compressed_file cf = this->c_files.at(filename);
    return getUncompressedData(cf.data.get(), cf.lfh.compressed_size);
}
