//
// Created by Kirill Zhukov on 05.02.2023.
//

/*!
 *  @brief bitmap used in malloc. Used for checking which page is used and can be deallocated if needed.
 */

#ifndef VM_WITH_HEAP_M_BITMAP_H
#define VM_WITH_HEAP_M_BITMAP_H
#include <string.h>
#include <stdlib.h>
#include "sys/types.h"

/// @brief used in TVM malloc
struct StaticBitmap {
    /*
     *
     * map: [00001111]
     *           ^
     *           |
     *      actually the size is 4 bits, so parameter `length` will be set to 4
     */
    size_t length;
    uint32_t map;
};
typedef struct StaticBitmap* bitmap_t;

/// @deprecated
/// @brief zero bitmap
/// @param bitmap bitmap to be zeroed
static inline void zero_bitmap(bitmap_t bitmap);
/// @brief setting bit
/// @param bitmap bitmap where bit will be set
/// @param n position where 1 will be set
/// @return -1 - success, otherwise 1
static inline int bitmap_set_bit(bitmap_t bitmap, unsigned n);
/// @brief clearing bit
/// @param bitmap bitmap where bit will be clear
/// @param n position where 0 will be set
/// @return -1 - success, otherwise 1
static inline int bitmap_clear_bit(bitmap_t bitmap, unsigned n);
/// @brief setting bit
/// @param bitmap bitmap where bit will be set
static inline size_t bitmap_nbits(bitmap_t bitmap);
/// @deprecated
/// @brief possible unnecessary
static inline char** bitmap_to_string();
/// @deprecated
/// @brief possible unnecessary
static inline int bitmap_from_string(char **c_str);



#endif //VM_WITH_HEAP_M_BITMAP_H
