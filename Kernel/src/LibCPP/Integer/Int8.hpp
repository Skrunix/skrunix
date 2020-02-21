#pragma once

#include <stdint.h>

struct Int8 {
	int8_t value;

	constexpr static const int8_t min = INT8_MIN;
	constexpr static const int8_t max = INT8_MAX;

	constexpr Int8(int8_t value)
	    : value(value) {}
};
static_assert(sizeof(Int8) == 1);
