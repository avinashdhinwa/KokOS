#pragma once

#include <stddef.h>
#include <stdint.h>

#include "cstring.hpp"

namespace mem
{
    void init(void);
    size_t used(void);
    size_t empty(void);
    void* alloc(const size_t length);
    void free(const void* const ptr);
    void* copy(const void* const ptrsrc, const size_t length);
    void* copy(const void* const ptrsrc);
    void* copy(const char* const str);
    void* dynalloc(const size_t initsize);
    void* dynresize(void* const ptr, const size_t newsize);

    // Memory size constants
    static const size_t MEMORY_SIZE_BYTES = 3 << 20;
    static const size_t MEMORY_SIZE_IN_SIZE_T = MEMORY_SIZE_BYTES / sizeof(size_t);
    static const size_t MEMORY_USED_BYTES_PER_ELEMENT = sizeof(size_t) * 8;
    static const size_t MEMORY_USED_SIZE = MEMORY_SIZE_BYTES / MEMORY_USED_BYTES_PER_ELEMENT;

    // Used for non-string memory allocations
    // Makes it possible to perform operations without specifying length of the segment
    static const size_t STATIC_SEGMENT_LIMIT = 1024;

    // Dynamic memory is being allocated / deallocated DYNAMIC_SEGMENT_SIZE bytes at a time
    static const size_t DYNAMIC_SEGMENT_SIZE = 256;
    static const size_t DYNAMIC_SEGMENT_LIMIT = MEMORY_SIZE_BYTES / DYNAMIC_SEGMENT_SIZE;
}

void operator delete(void* ptr);
