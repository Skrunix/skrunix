#pragma once

#include <stdint.h>

struct Int16 {
	int16_t value;

	constexpr static const int16_t min = INT16_MIN;
	constexpr static const int16_t max = INT16_MAX;

	constexpr Int16(int16_t value)
	    : value(value) {}
};
static_assert(sizeof(Int16) == 2);
