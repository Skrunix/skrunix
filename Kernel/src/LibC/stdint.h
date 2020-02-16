#pragma once

#define INT8_MIN 0x80
#define INT16_MIN 0x8000
#define INT32_MIN 0x80000000
#define INT64_MIN 0x8000000000000000

#define SSIZE_MIN INT64_MIN
#define INTMAX_MIN INT64_MIN
#define INTPTR_MIN INT64_MIN

#define INT8_MAX 0x7F
#define INT16_MAX 0x7FFF
#define INT32_MAX 0x7FFFFFFF
#define INT64_MAX 0x7FFFFFFFFFFFFFFF

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT64_MAX 0xFFFFFFFFFFFFFFFF

#define SSIZE_MAX INT64_MAX
#define SIZE_MAX UINT64_MAX

#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define INTPTR_MAX INT64_MAX
#define UINTPTR_MAX UINT64_MAX

#define PTRDIFF_MAX UINT64_MAX

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
