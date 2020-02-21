#pragma once

#include <stdint.h>

struct Int {
	intmax_t value;

	constexpr static const intmax_t min = INTMAX_MIN;
	constexpr static const intmax_t max = INTMAX_MAX;

	constexpr Int(intmax_t value)
	    : value(value) {}
};
static_assert(sizeof(Int) == 8);
