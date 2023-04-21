//
// Created by Kirill Zhukov on 05.02.2023.
//
#include "m_bitmap.h"

int bitmap_set_bit(bitmap_t bitmap, unsigned n) {
    if (n > sizeof(bitmap->map) * 8) return -1;
    bitmap->map |= (0b1 << n);
    return 1;
}

int bitmap_clear_bit(bitmap_t bitmap, unsigned n) {
    if (n > sizeof(bitmap->map) * 8) return -1;
    bitmap->map |= (0b0 << n);
    return 1;
}