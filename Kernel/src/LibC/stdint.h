#pragma once

typedef signed char      int8_t;
typedef signed short     int16_t;
typedef signed int       int32_t;
typedef signed long long int64_t;

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef int64_t  ssize_t;
typedef uint64_t size_t;

typedef int64_t  intmax_t;
typedef uint64_t uintmax_t;

typedef int64_t  intptr_t;
typedef uint64_t uintptr_t;

typedef uint64_t ptrdiff_t;

#if defined(__cplusplus)
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);

static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);

static_assert(sizeof(ssize_t) == 8);
static_assert(sizeof(size_t) == 8);

static_assert(sizeof(intmax_t) == 8);
static_assert(sizeof(uintmax_t) == 8);

static_assert(sizeof(intptr_t) == 8);
static_assert(sizeof(uintptr_t) == 8);

static_assert(sizeof(ptrdiff_t) == 8);
#endif
