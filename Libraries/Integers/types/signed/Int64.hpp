#pragma once

#include "Int32.hpp"

struct [[gnu::packed]] Int64 {
	using BackingType = int64_t;

	constexpr static BackingType Min = INT64_MIN;
	constexpr static BackingType Max = INT64_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	constexpr Int64()
	    : value(0) {}
	constexpr Int64(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline Int64 operator+(Int64 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline Int64 operator-(Int64 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline Int64 operator*(Int64 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline Int64 operator/(Int64 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline Int64 operator&(Int64 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline Int64 operator|(Int64 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline Int64 operator^(Int64 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline Int64 operator<<(Int64 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline Int64 operator>>(Int64 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(Int64 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(Int64 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(Int64 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(Int64 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(Int64 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(Int64 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline Int64& operator+=(const Int64& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int64& operator-=(const Int64& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int64& operator*=(const Int64& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int64& operator/=(const Int64& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline Int64& operator&=(const Int64& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int64& operator|=(const Int64& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int64& operator^=(const Int64& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline Int64& operator<<=(const Int64& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int64& operator>>=(const Int64& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline Int64  operator-() { return -this->value; }
	[[gnu::always_inline]] inline Int64  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline Int64& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline Int64& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline Int64 operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline Int64 operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(Int64) == 8);
