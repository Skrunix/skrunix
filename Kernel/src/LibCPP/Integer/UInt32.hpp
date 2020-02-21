#pragma once

#include <stdint.h>

struct UInt32 {
	uint32_t value;

	constexpr static const uint32_t min = UINT32_MIN;
	constexpr static const uint32_t max = UINT32_MAX;

	constexpr UInt32(uint32_t value)
	    : value(value) {}
};
static_assert(sizeof(UInt32) == 4);
