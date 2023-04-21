//
// Created by Kirill Zhukov on 31.01.2023.
//

#include "Symbol.h"

u2 Symbol::getLength() const {
    return _length;
}

void Symbol::setLength(u2 length) {
    _length = length;
}

const char *Symbol::getBody() const {
    return _body;
}

void Symbol::setBody(const char *body) {
    _body = (cstring)body;
}

uint32_t Symbol::getHash() const {
    return _hash;
}

void Symbol::setHash(uint32_t hash) {
    _hash = hash;
}

Symbol::Symbol(u2 length, const char *body, uint64_t hash) : _length(length), _body(const_cast<cstring>(body)), _hash(hash) {}