//
// Created by Kirill Zhukov on 13.03.2023.
//
#include "chunk.h"

void setChunkSize(chunk_t ch, size_t sz) {
    ch->size = sz;
}