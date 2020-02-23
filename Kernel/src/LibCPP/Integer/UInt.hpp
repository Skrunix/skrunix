#pragma once

#include <stdint.h>

struct [[gnu::packed]] UInt {
	using BackingType = uintmax_t;

	BackingType value;

	constexpr static const BackingType min = UINTMAX_MIN;
	constexpr static const BackingType max = UINTMAX_MAX;

	constexpr UInt()
	    : value(0) {}
	constexpr UInt(BackingType value)
	    : value(value) {}

	inline UInt operator&(UInt rhs) { return value & rhs.value; };
};
static_assert(sizeof(UInt) == 8);
