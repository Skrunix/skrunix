#pragma once

#include "UInt32.hpp"

struct [[gnu::packed]] UInt {
	using BackingType = uintmax_t;

	constexpr static BackingType Min = UINTMAX_MIN;
	constexpr static BackingType Max = UINTMAX_MAX;

	constexpr static int         BitWidth = 64ull;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	constexpr UInt()
	    : value(0) {}
	constexpr UInt(BackingType value)
	    : value(value) {}

	[[gnu::always_inline]] inline UInt32 low() {
		return this->value & HalfMask;
	}
	[[gnu::always_inline]] inline UInt32 high() {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline UInt operator+(UInt rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline UInt operator-(UInt rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline UInt operator*(UInt rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline UInt operator/(UInt rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline UInt operator&(UInt rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline UInt operator|(UInt rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline UInt operator^(UInt rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline UInt operator<<(UInt rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline UInt operator>>(UInt rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(UInt rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(UInt rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(UInt rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(UInt rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(UInt rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(UInt rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline UInt& operator+=(const UInt& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt& operator-=(const UInt& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt& operator*=(const UInt& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt& operator/=(const UInt& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline UInt& operator&=(const UInt& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt& operator|=(const UInt& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt& operator^=(const UInt& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline UInt& operator<<=(const UInt& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt& operator>>=(const UInt& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline UInt  operator-() { return -this->value; }
	[[gnu::always_inline]] inline UInt  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline UInt& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline UInt& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline UInt operator++(int) { return this->value++; }
	[[gnu::always_inline]] inline UInt operator--(int) { return this->value--; }
};
static_assert(sizeof(UInt) == 8);
