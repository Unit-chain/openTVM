//
// Created by Kirill Zhukov on 09.12.2022.
//

#ifndef VM_WITH_HEAP_BLOOMFILTER_H
#define VM_WITH_HEAP_BLOOMFILTER_H
#include <vector>
#include "bloomhash.h"

class BloomFilter {
public:
    virtual ~BloomFilter();
private:
    BloomFilter(uint64_t size, uint8_t numHashes, BloomHash *hash) : m_size(size), m_numHashes(numHashes), m_hash(hash) {};
    void add(const uint8_t *data, std::size_t len);
    bool possiblyContains(const uint8_t *data, std::size_t len) const;
    inline static uint64_t nthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t filterSize) {
        return (hashA + n * hashB) % filterSize;
    }
private:
    uint64_t m_size;
    uint8_t m_numHashes;
    std::vector<bool> m_bits;
    BloomHash *m_hash;
};

void BloomFilter::add(const uint8_t *data, std::size_t len) {
    auto hashValues = m_hash->u128_hash(data, len);
    for (int n = 0; n < this->m_numHashes; n++) {
        this->m_bits[nthHash(n, hashValues[0], hashValues[1], this->m_size)] = true;
    }
}

bool BloomFilter::possiblyContains(const uint8_t *data, std::size_t len) const {
    auto hashValues = m_hash->u128_hash(data, len);
    for (int n = 0; n < m_numHashes; n++) {
        if (!m_bits[nthHash(n, hashValues[0], hashValues[1], m_size)]) {
            return false;
        }
    }
    return true;
}

BloomFilter::~BloomFilter() {
    delete this->m_hash;
    this->m_hash = nullptr;
}

#endif //VM_WITH_HEAP_BLOOMFILTER_H
