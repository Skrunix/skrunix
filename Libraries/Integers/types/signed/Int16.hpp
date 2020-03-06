#pragma once

#include "Int8.hpp"

struct [[gnu::packed]] Int16 {
	using BackingType = int16_t;

	constexpr static BackingType Min = INT16_MIN;
	constexpr static BackingType Max = INT16_MAX;

	constexpr static int BitWidth = 16u;

	BackingType value;

	constexpr Int16()
	    : value(0) {}
	constexpr Int16(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline Int16 operator+(Int16 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline Int16 operator-(Int16 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline Int16 operator*(Int16 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline Int16 operator/(Int16 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline Int16 operator&(Int16 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline Int16 operator|(Int16 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline Int16 operator^(Int16 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline Int16 operator<<(Int16 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline Int16 operator>>(Int16 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(Int16 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(Int16 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(Int16 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(Int16 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(Int16 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(Int16 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline Int16& operator+=(const Int16& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int16& operator-=(const Int16& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int16& operator*=(const Int16& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int16& operator/=(const Int16& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline Int16& operator&=(const Int16& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int16& operator|=(const Int16& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int16& operator^=(const Int16& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline Int16& operator<<=(const Int16& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int16& operator>>=(const Int16& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline Int16  operator-() { return -this->value; }
	[[gnu::always_inline]] inline Int16  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline Int16& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline Int16& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline Int16 operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline Int16 operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(Int16) == 2);
