//
// Created by Kirill Zhukov on 08.05.2023.
//

#include "CustomHash.h"

size_t CustomHash::operator()(const std::string &s) const {
    return wyhash(s.data(), s.size(), 0, _wyp);
}