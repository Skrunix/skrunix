#pragma once

#include <stdint.h>

struct [[gnu::packed]] UInt {
	using BackingType = uintmax_t;

	BackingType value;

	constexpr static const BackingType min = UINTMAX_MIN;
	constexpr static const BackingType max = UINTMAX_MAX;

	constexpr UInt()
	    : value(0) {}
	constexpr UInt(BackingType value)
	    : value(value) {}

	inline UInt operator&(UInt rhs) { return value & rhs.value; };

	inline bool operator<(UInt rhs) { return value < rhs.value; };

	// Prefix
	inline UInt& operator++() {
		++value;
		return *this;
	}
	inline UInt& operator--() {
		--value;
		return *this;
	}

	// Postfix
	inline UInt operator++(int) { return value++; }
	inline UInt operator--(int) { return value--; }
};
static_assert(sizeof(UInt) == 8);
