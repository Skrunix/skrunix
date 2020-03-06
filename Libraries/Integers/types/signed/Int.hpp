#pragma once

#include "Int32.hpp"

struct [[gnu::packed]] Int {
	using BackingType = intmax_t;

	constexpr static BackingType Min = INTMAX_MIN;
	constexpr static BackingType Max = INTMAX_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	constexpr Int()
	    : value(0) {}
	constexpr Int(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline Int operator+(Int rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline Int operator-(Int rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline Int operator*(Int rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline Int operator/(Int rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline Int operator&(Int rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline Int operator|(Int rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline Int operator^(Int rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline Int operator<<(Int rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline Int operator>>(Int rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(Int rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(Int rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(Int rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(Int rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(Int rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(Int rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline Int& operator+=(const Int& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int& operator-=(const Int& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int& operator*=(const Int& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int& operator/=(const Int& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline Int& operator&=(const Int& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int& operator|=(const Int& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int& operator^=(const Int& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline Int& operator<<=(const Int& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int& operator>>=(const Int& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline Int  operator-() { return -this->value; }
	[[gnu::always_inline]] inline Int  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline Int& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline Int& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline Int operator++(int) { return this->value++; }
	[[gnu::always_inline]] inline Int operator--(int) { return this->value--; }
};
static_assert(sizeof(Int) == 8);
