#ifndef TH_HASH_H
#define TH_HASH_H

#include "stdint.h"
#include "string.h"

/**
 * wyhash32. original: https://github.com/wangyi-fudan/wyhash
 */

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned _wyr32(const uint8_t *p);
extern inline unsigned _wyr24(const uint8_t *p, unsigned k);
extern inline void _wymix32(unsigned *A, unsigned *B);
extern inline unsigned wyhash32(const void *key, uint64_t len, unsigned seed);

#ifdef __cplusplus
}
#endif

#endif // TH_HASH_H