#pragma once

#include <stdint.h>

struct [[gnu::packed]] Int16 {
	using BackingType = int16_t;

	BackingType value;

	constexpr static const BackingType min = INT16_MIN;
	constexpr static const BackingType max = INT16_MAX;

	constexpr Int16()
	    : value(0) {}
	constexpr Int16(BackingType value)
	    : value(value) {}
};
static_assert(sizeof(Int16) == 2);
