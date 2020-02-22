#pragma once

#include <stdint.h>

struct __attribute__((packed)) Int8 {
	using BackingType = int8_t;
	
	BackingType value;

	constexpr static const BackingType min = INT8_MIN;
	constexpr static const BackingType max = INT8_MAX;

	constexpr Int8()
	    : value(0) {}
	constexpr Int8(BackingType value)
	    : value(value) {}
};
static_assert(sizeof(Int8) == 1);
