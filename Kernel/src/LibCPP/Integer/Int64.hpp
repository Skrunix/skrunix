#pragma once

#include <stdint.h>

struct Int64 {
	int64_t value;

	constexpr static const int64_t min = INT64_MIN;
	constexpr static const int64_t max = INT64_MAX;

	constexpr Int64(int64_t value)
	    : value(value) {}
};
static_assert(sizeof(Int64) == 8);
