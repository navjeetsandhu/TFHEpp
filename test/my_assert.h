#pragma once

#include <cstdio>
#include <cstdlib>

#define ASSERT(condition) \
do { \
    if (!(condition)) { \
        fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %d.\n", __FUNCTION__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (false)