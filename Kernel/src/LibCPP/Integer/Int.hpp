#pragma once

#include <stdint.h>

struct [[gnu::packed]] Int {
	using BackingType = intmax_t;

	BackingType value;

	constexpr static const BackingType min = INTMAX_MIN;
	constexpr static const BackingType max = INTMAX_MAX;

	constexpr Int()
	    : value(0) {}
	constexpr Int(BackingType value)
	    : value(value) {}
};
static_assert(sizeof(Int) == 8);
