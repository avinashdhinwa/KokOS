#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C"
{
#endif

size_t strlen(const char* const str);
bool strcmp(const char* const str1, const char* const str2);
char* tostr(const size_t input, const size_t base);
size_t strparse(const char* const str, const size_t base);
char* strjoin(const char* const str1, const char* const str2);
void strcopy(const char* const strInput, char* const strOutput);
char ctoupper(const char c);
char ctolower(const char c);
void strtoupper(char* const str);
void strtolower(char* const str);
size_t strfirst(const char* const str, const char c);
size_t strlast(const char* const str, const char c);
char* strfill(const char c, const size_t count);
char* colorToStr(const uint8_t color);

#if defined(__cplusplus)
}
#endif
