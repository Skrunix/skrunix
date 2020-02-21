#pragma once

#include <stdint.h>

struct UInt64 {
	uint64_t value;

	constexpr static const uint64_t min = UINT64_MIN;
	constexpr static const uint64_t max = UINT64_MAX;

	constexpr UInt64(uint64_t value)
	    : value(value) {}
};
static_assert(sizeof(UInt64) == 8);
