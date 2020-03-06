#pragma once

#include <stdint.h>

struct [[gnu::packed]] Int8 {
	using BackingType = int8_t;

	constexpr static BackingType Min = INT8_MIN;
	constexpr static BackingType Max = INT8_MAX;

	constexpr static int BitWidth = 8u;

	BackingType value;

	constexpr Int8()
	    : value(0) {}
	constexpr Int8(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline Int8 operator+(Int8 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline Int8 operator-(Int8 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline Int8 operator*(Int8 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline Int8 operator/(Int8 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline Int8 operator&(Int8 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline Int8 operator|(Int8 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline Int8 operator^(Int8 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline Int8 operator<<(Int8 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline Int8 operator>>(Int8 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(Int8 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(Int8 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(Int8 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(Int8 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(Int8 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(Int8 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline Int8& operator+=(const Int8& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int8& operator-=(const Int8& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int8& operator*=(const Int8& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int8& operator/=(const Int8& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline Int8& operator&=(const Int8& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int8& operator|=(const Int8& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int8& operator^=(const Int8& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline Int8& operator<<=(const Int8& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int8& operator>>=(const Int8& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline Int8  operator-() { return -this->value; }
	[[gnu::always_inline]] inline Int8  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline Int8& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline Int8& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline Int8 operator++(int) { return this->value++; }
	[[gnu::always_inline]] inline Int8 operator--(int) { return this->value--; }
};
static_assert(sizeof(Int8) == 1);
