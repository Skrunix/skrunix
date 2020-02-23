#pragma once

#include <stdint.h>

struct [[gnu::packed]] UInt8 {
	using BackingType = uint8_t;

	BackingType value;

	constexpr static const BackingType min = UINT8_MIN;
	constexpr static const BackingType max = UINT8_MAX;

	constexpr UInt8()
	    : value(0) {}
	constexpr UInt8(BackingType value)
	    : value(value) {}

	inline UInt8 low() { return value & 0x0F; }
	inline UInt8 high() { return (value >> 4) & 0x0F; }

	inline UInt8 operator&(UInt8 rhs) { return value & rhs.value; };
	inline UInt8 operator|(UInt8 rhs) { return value | rhs.value; };

	inline UInt8 operator<<(UInt8 rhs) { return value >> rhs.value; };

	inline bool operator>(UInt8 rhs) { return value > rhs.value; };
	inline bool operator<(UInt8 rhs) { return value < rhs.value; };
	inline bool operator==(UInt8 rhs) { return value == rhs.value; };
	inline bool operator!=(UInt8 rhs) { return value != rhs.value; };

	inline UInt8& operator-=(const UInt8& rhs) {
		value -= rhs.value;
		return *this;
	};

	// Prefix
	inline UInt8& operator++() {
		++value;
		return *this;
	}
	inline UInt8& operator--() {
		--value;
		return *this;
	}

	// Postfix
	inline UInt8 operator++(int) { return value++; }
	inline UInt8 operator--(int) { return value--; }
};
static_assert(sizeof(UInt8) == 1);
