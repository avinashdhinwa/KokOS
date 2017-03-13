#pragma once

#include "stdtypes.hpp"
#include "memory.hpp"

namespace str
{
    size_t len(const char* const str);
    bool cmp(const char* const str1, const char* const str2);
    char* convert(const size_t input, const size_t base = 10);
    size_t parse(const char* const str, const size_t base = 10);
}