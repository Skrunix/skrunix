#pragma once

#include <stdint.h>

struct UInt8 {
	uint8_t value;

	constexpr static const uint8_t min = UINT8_MIN;
	constexpr static const uint8_t max = UINT8_MAX;

	constexpr UInt8(uint8_t value)
	    : value(value) {}

	inline UInt8 low() { return value & 0x0F; }
	inline UInt8 high() { return (value >> 4) & 0x0F; }

	inline UInt8 operator&(UInt8 rhs) { return value & rhs.value; };
	inline UInt8 operator|(UInt8 rhs) { return value | rhs.value; };

	inline bool operator==(UInt8 rhs) { return value == rhs.value; };
	inline bool operator!=(UInt8 rhs) { return value != rhs.value; };
};
static_assert(sizeof(UInt8) == 1);
