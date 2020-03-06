#pragma once

#include <stdint.h>

struct [[gnu::packed]] Size {
	using BackingType = ssize_t;

	constexpr static BackingType Min = SSIZE_MIN;
	constexpr static BackingType Max = SSIZE_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	constexpr Size()
	    : value(0) {}
	constexpr Size(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline Size operator+(Size rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline Size operator-(Size rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline Size operator*(Size rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline Size operator/(Size rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline Size operator&(Size rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline Size operator|(Size rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline Size operator^(Size rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline Size operator<<(Size rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline Size operator>>(Size rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(Size rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(Size rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(Size rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(Size rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(Size rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(Size rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline Size& operator+=(const Size& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Size& operator-=(const Size& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Size& operator*=(const Size& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Size& operator/=(const Size& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline Size& operator&=(const Size& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Size& operator|=(const Size& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Size& operator^=(const Size& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline Size& operator<<=(const Size& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline Size& operator>>=(const Size& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline Size  operator-() { return -this->value; }
	[[gnu::always_inline]] inline Size  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline Size& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline Size& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline Size operator++(int) { return this->value++; }
	[[gnu::always_inline]] inline Size operator--(int) { return this->value--; }
};
static_assert(sizeof(Size) == 8);
