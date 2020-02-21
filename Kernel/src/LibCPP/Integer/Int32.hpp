#pragma once

#include <stdint.h>

struct Int32 {
	int32_t value;

	constexpr static const int32_t min = INT32_MIN;
	constexpr static const int32_t max = INT32_MAX;

	constexpr Int32(int32_t value)
	    : value(value) {}
};
static_assert(sizeof(Int32) == 4);
