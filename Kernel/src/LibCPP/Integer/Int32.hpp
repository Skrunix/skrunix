#pragma once

#include <stdint.h>

struct [[gnu::packed]] Int32 {
	using BackingType = int32_t;

	BackingType value;

	constexpr static const BackingType min = INT32_MIN;
	constexpr static const BackingType max = INT32_MAX;

	constexpr Int32()
	    : value(0) {}
	constexpr Int32(BackingType value)
	    : value(value) {}
};
static_assert(sizeof(Int32) == 4);
