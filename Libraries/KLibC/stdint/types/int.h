#pragma once

#include <assert.h>

typedef signed char      int8_t;
typedef signed short     int16_t;
typedef signed int       int32_t;
typedef signed long long int64_t;

typedef int64_t intmax_t;
typedef int64_t intptr_t;
typedef int64_t ssize_t;

static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);

static_assert(sizeof(intmax_t) == 8);
static_assert(sizeof(intptr_t) == 8);
static_assert(sizeof(ssize_t) == 8);
