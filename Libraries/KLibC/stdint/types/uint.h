#pragma once

#include <assert.h>

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef uint64_t uintmax_t;
typedef uint64_t uintptr_t;
typedef uint64_t size_t;
typedef uint64_t ptrdiff_t;

static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);

static_assert(sizeof(uintmax_t) == 8);
static_assert(sizeof(uintptr_t) == 8);
static_assert(sizeof(size_t) == 8);
static_assert(sizeof(ptrdiff_t) == 8);
