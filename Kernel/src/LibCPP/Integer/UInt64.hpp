#pragma once

#include <stdint.h>

struct [[gnu::packed]] UInt64 {
	using BackingType = uint64_t;

	BackingType value;

	constexpr static const BackingType min = UINT64_MIN;
	constexpr static const BackingType max = UINT64_MAX;

	constexpr UInt64()
	    : value(0) {}
	constexpr UInt64(BackingType value)
	    : value(value) {}

	inline bool operator==(UInt64 rhs) { return value == rhs.value; };

	// Prefix
	inline UInt64& operator++() {
		++value;
		return *this;
	}
	inline UInt64& operator--() {
		--value;
		return *this;
	}

	// Postfix
	inline UInt64 operator++(int) { return value++; }
	inline UInt64 operator--(int) { return value--; }
};
static_assert(sizeof(UInt64) == 8);
