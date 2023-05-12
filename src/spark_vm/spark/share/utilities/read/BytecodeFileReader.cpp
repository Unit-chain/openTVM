//
// Created by Kirill Zhukov on 08.05.2023.
//

#include "BytecodeFileReader.h"

BytecodeFileReader::BytecodeFileReader(std::string &path) {
    this->path = path;
}



void BytecodeFileReader::read_program() {
        int err = 0;
        zip_t *zip = zip_open(this->path.c_str(), 0, &err);
        if (zip == NULL) {
            zip_error_t ziperror;
            zip_error_init_with_code(&ziperror, err);
            std::cerr << "Failed to open zip file: " << zip_error_strerror(&ziperror) << std::endl;
            zip_error_fini(&ziperror);
            return;
        }

        zip_int64_t num_entries = zip_get_num_entries(zip, 0);
        this->files.reserve(num_entries);
        for (zip_int64_t i = 0; i < num_entries; ++i) {
            struct zip_stat st;
            zip_stat_init(&st);
            if (zip_stat_index(zip, i, 0, &st) != 0) {
                std::cerr << "Failed to stat file: " << zip_strerror(zip) << std::endl;
                zip_close(zip);
                return;
            }
            std::string name = st.name;
            if (name.back() == '/') {
                name.pop_back();
            }
            zip_file_t *file = zip_fopen_index(zip, i, 0);
            if (!file) {
                std::cerr << "Failed to open file: " << zip_strerror(zip) << std::endl;
                zip_close(zip);
                return;
            }
            char *buffer = (char *) std::malloc(st.size);
            zip_int64_t read_size = zip_fread(file, buffer, st.size);
            if (read_size > 0) {
                this->files.insert_or_assign(name, std::shared_ptr<char>(buffer));
            }
            zip_fclose(file);
#if 0
            std::free(buffer);
#endif
        }

        if (zip_close(zip) == -1) {
            std::cerr << "Failed to close zip file: " << zip_strerror(zip) << std::endl;
            return;
        }
}

const std::unordered_map<std::string, std::shared_ptr<char>, CustomHash> &BytecodeFileReader::getFiles() const {
    return files;
}

std::shared_ptr<char> BytecodeFileReader::getUncompressedProgram(const std::string& filename) {
    if (this->files.empty()) {
        this->read_program();
    }
    if (!this->files.contains(filename)) {
        return nullptr;
    }
    return this->files.at(filename);
}

