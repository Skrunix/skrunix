#pragma once

#include "UInt8.hpp"

struct [[gnu::packed]] UInt16 {
	using BackingType = uint16_t;

	constexpr static BackingType Min = UINT16_MIN;
	constexpr static BackingType Max = UINT16_MAX;

	constexpr static int BitWidth = 16u;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	constexpr UInt16()
	    : value(0) {}
	constexpr UInt16(BackingType value)
	    : value(value) {}

	[[gnu::always_inline]] inline UInt8 low() { return this->value & HalfMask; }
	[[gnu::always_inline]] inline UInt8 high() {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline UInt16 operator+(UInt16 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline UInt16 operator-(UInt16 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline UInt16 operator*(UInt16 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline UInt16 operator/(UInt16 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline UInt16 operator&(UInt16 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline UInt16 operator|(UInt16 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline UInt16 operator^(UInt16 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline UInt16 operator<<(UInt16 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline UInt16 operator>>(UInt16 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(UInt16 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(UInt16 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(UInt16 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(UInt16 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(UInt16 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(UInt16 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline UInt16& operator+=(const UInt16& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt16& operator-=(const UInt16& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt16& operator*=(const UInt16& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt16& operator/=(const UInt16& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline UInt16& operator&=(const UInt16& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt16& operator|=(const UInt16& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt16& operator^=(const UInt16& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline UInt16& operator<<=(const UInt16& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt16& operator>>=(const UInt16& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline UInt16  operator-() { return -this->value; }
	[[gnu::always_inline]] inline UInt16  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline UInt16& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline UInt16& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline UInt16 operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline UInt16 operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(UInt16) == 2);
