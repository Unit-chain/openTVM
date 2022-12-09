//
// Created by Kirill Zhukov on 09.12.2022.
//

#ifndef VM_WITH_HEAP_BLOOMHASH_H
#define VM_WITH_HEAP_BLOOMHASH_H
#include "cstdlib"
#include "array"
#include "hash/xxhash.h"

class BloomHash {
public:
    virtual ~BloomHash() = default;
    virtual uint32_t u32_hash(const void* value, std::size_t len) = 0;
    virtual uint64_t u64_hash(const void* value, std::size_t len) = 0;
    virtual std::array<uint64_t, 2> u128_hash(const void* value, std::size_t len) = 0;
};


class XXHashBloomHash : public BloomHash {
public:
    uint32_t u32_hash(const void* value, std::size_t len) override {
        return XXH32(value, len, 29900);
    }
    uint64_t u64_hash(const void* value, std::size_t len) override {
        return XXH64(value, len, 29900);
    }
    std::array<uint64_t, 2> u128_hash(const void* value, std::size_t len) override {
        XXH128_hash_t hash = XXH3_128bits(value, len);
        return {hash.high64, hash.low64};
    }
};

#endif //VM_WITH_HEAP_BLOOMHASH_H
