#pragma once

#include <stdint.h>

struct [[gnu::packed]] Int64 {
	using BackingType = int64_t;

	BackingType value;

	constexpr static const BackingType min = INT64_MIN;
	constexpr static const BackingType max = INT64_MAX;

	constexpr Int64()
	    : value(0) {}
	constexpr Int64(BackingType value)
	    : value(value) {}
};
static_assert(sizeof(Int64) == 8);
