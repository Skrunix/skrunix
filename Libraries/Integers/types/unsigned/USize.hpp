#pragma once

#include <stdint.h>

struct [[gnu::packed]] USize {
	using BackingType = size_t;

	constexpr static BackingType Min = SIZE_MIN;
	constexpr static BackingType Max = SIZE_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	constexpr USize()
	    : value(0) {}
	constexpr USize(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline USize operator+(USize rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline USize operator-(USize rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline USize operator*(USize rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline USize operator/(USize rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline USize operator&(USize rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline USize operator|(USize rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline USize operator^(USize rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline USize operator<<(USize rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline USize operator>>(USize rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(USize rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(USize rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(USize rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(USize rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(USize rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(USize rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline USize& operator+=(const USize& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline USize& operator-=(const USize& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline USize& operator*=(const USize& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline USize& operator/=(const USize& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline USize& operator&=(const USize& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline USize& operator|=(const USize& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline USize& operator^=(const USize& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline USize& operator<<=(const USize& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline USize& operator>>=(const USize& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline USize  operator-() { return -this->value; }
	[[gnu::always_inline]] inline USize  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline USize& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline USize& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline USize operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline USize operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(USize) == 8);
