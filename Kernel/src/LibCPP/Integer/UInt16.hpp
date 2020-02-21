#pragma once

#include <Integer/UInt8.hpp>

struct UInt16 {
	uint16_t value;

	constexpr static const uint16_t min = UINT16_MIN;
	constexpr static const uint16_t max = UINT16_MAX;

	constexpr UInt16(uint16_t value)
	    : value(value) {}

	inline UInt8 low() { return value & 0xFF; }
	inline UInt8 high() { return (value >> 8) & 0xFF; }

	inline UInt16 operator+(UInt16 rhs) { return value + rhs.value; };
	inline UInt16 operator-(UInt16 rhs) { return value - rhs.value; };
	inline UInt16 operator*(UInt16 rhs) { return value * rhs.value; };

	inline UInt16 operator>>(UInt16 rhs) { return value >> rhs.value; };

	inline bool operator<(UInt16 rhs) { return value < rhs.value; };
	inline bool operator>(UInt16 rhs) { return value > rhs.value; };
	inline bool operator>=(UInt16 rhs) { return value >= rhs.value; };

	// Prefix
	inline UInt16& operator++() {
		++value;
		return *this;
	}
	inline UInt16& operator--() {
		--value;
		return *this;
	}

	// Postfix
	inline UInt16 operator++(int) { return value++; }
	inline UInt16 operator--(int) { return value--; }
};
static_assert(sizeof(UInt16) == 2);
