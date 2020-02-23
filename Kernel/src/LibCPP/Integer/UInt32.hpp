#pragma once

#include <Integer/UInt16.hpp>

struct [[gnu::packed]] UInt32 {
	using BackingType = uint32_t;

	BackingType value;

	constexpr static const BackingType min = UINT32_MIN;
	constexpr static const BackingType max = UINT32_MAX;

	constexpr UInt32()
	    : value(0) {}
	constexpr UInt32(BackingType value)
	    : value(value) {}
	constexpr UInt32(UInt16 value)
	    : value(value.value) {}

	inline UInt16 low() { return value & 0xFFFF; }
	inline UInt16 high() { return (value >> 16) & 0xFFFF; }

	inline UInt32 operator/(UInt32 rhs) { return value / rhs.value; };

	inline UInt32 operator&(UInt32 rhs) { return value & rhs.value; };

	inline UInt32 operator>>(UInt32 rhs) { return value >> rhs.value; };

	inline bool operator==(UInt32 rhs) { return value == rhs.value; };
};
static_assert(sizeof(UInt32) == 4);
