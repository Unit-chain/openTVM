//
// Created by Kirill Zhukov on 31.01.2023.
//

#ifndef VM_WITH_HEAP_SYMBOL_H
#define VM_WITH_HEAP_SYMBOL_H
#include "memory/metaObject.h"
#include "global/globalDefenitions.h"

class Symbol : public metaObject {
public:
    u2 _length;
    cstring _body;
    volatile uint32_t _hash;

    Symbol() = default;
    Symbol(u2 length, const char *body, uint32_t hash);

    [[nodiscard]] uint32_t getHash() const;
    void setHash(uint32_t hash);
    [[nodiscard]] u2 getLength() const;
    void setLength(u2 length);
    [[nodiscard]] const char *getBody() const;
    void setBody(const char *body);
};


#endif //VM_WITH_HEAP_SYMBOL_H
