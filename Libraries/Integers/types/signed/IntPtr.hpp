#pragma once

#include <stdint.h>

struct [[gnu::packed]] IntPtr {
	using BackingType = intptr_t;

	constexpr static BackingType Min = INTPTR_MIN;
	constexpr static BackingType Max = INTPTR_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	constexpr IntPtr()
	    : value(0) {}
	constexpr IntPtr(BackingType value)
	    : value(value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}
	template <typename T>
	[[gnu::always_inline]] inline explicit operator T*() const {
		return reinterpret_cast<T*>(this->value);
	}

	// Arithmetic
	[[gnu::always_inline]] inline IntPtr operator+(IntPtr rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline IntPtr operator-(IntPtr rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline IntPtr operator*(IntPtr rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline IntPtr operator/(IntPtr rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline IntPtr operator&(IntPtr rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline IntPtr operator|(IntPtr rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline IntPtr operator^(IntPtr rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline IntPtr operator<<(IntPtr rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline IntPtr operator>>(IntPtr rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(IntPtr rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(IntPtr rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(IntPtr rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(IntPtr rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(IntPtr rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(IntPtr rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline IntPtr& operator+=(const IntPtr& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline IntPtr& operator-=(const IntPtr& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline IntPtr& operator*=(const IntPtr& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline IntPtr& operator/=(const IntPtr& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline IntPtr& operator&=(const IntPtr& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline IntPtr& operator|=(const IntPtr& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline IntPtr& operator^=(const IntPtr& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline IntPtr& operator<<=(const IntPtr& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline IntPtr& operator>>=(const IntPtr& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline IntPtr  operator-() { return -this->value; }
	[[gnu::always_inline]] inline IntPtr  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline IntPtr& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline IntPtr& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline IntPtr operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline IntPtr operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(IntPtr) == 8);
