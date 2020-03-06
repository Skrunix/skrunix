#pragma once

#include "Int16.hpp"

struct [[gnu::packed]] Int32 {
	using BackingType = int32_t;

	constexpr static BackingType Min = INT32_MIN;
	constexpr static BackingType Max = INT32_MAX;

	constexpr static int BitWidth = 32ul;

	BackingType value;

	constexpr Int32()
	    : value(0) {}
	constexpr Int32(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline Int32 operator+(Int32 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline Int32 operator-(Int32 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline Int32 operator*(Int32 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline Int32 operator/(Int32 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline Int32 operator&(Int32 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline Int32 operator|(Int32 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline Int32 operator^(Int32 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline Int32 operator<<(Int32 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline Int32 operator>>(Int32 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(Int32 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(Int32 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(Int32 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(Int32 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(Int32 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(Int32 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline Int32& operator+=(const Int32& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int32& operator-=(const Int32& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int32& operator*=(const Int32& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int32& operator/=(const Int32& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline Int32& operator&=(const Int32& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int32& operator|=(const Int32& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int32& operator^=(const Int32& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline Int32& operator<<=(const Int32& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Int32& operator>>=(const Int32& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline Int32  operator-() { return -this->value; }
	[[gnu::always_inline]] inline Int32  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline Int32& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline Int32& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline Int32 operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline Int32 operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(Int32) == 4);
