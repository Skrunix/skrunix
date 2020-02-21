#pragma once

#include <stdint.h>

struct UInt {
	uintmax_t value;

	constexpr static const uintmax_t min = UINTMAX_MIN;
	constexpr static const uintmax_t max = UINTMAX_MAX;

	constexpr UInt(uintmax_t value)
	    : value(value) {}
};
static_assert(sizeof(UInt) == 8);
