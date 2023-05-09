//
// Created by Kirill Zhukov on 08.05.2023.
//

#include "CustomHash.h"

size_t CustomHash::operator()(const std::string &s) const {
    size_t t = wyhash32(s.c_str(), s.length(), seeds[seed_round]) % MAP_MODULO;
    seed_round++;
    seed_round %= 12;
    return t;
}

size_t CustomHash::operator()(unsigned long long k) const {
    char foo[20];
    snprintf(foo, 20, "%#016llx", k);
    size_t t = wyhash32(foo, 20, seeds[seed_round]) % MAP_MODULO;
    seed_round++;
    seed_round %= 12;
    return t;
}