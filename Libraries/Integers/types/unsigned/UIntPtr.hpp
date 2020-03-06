#pragma once

#include "UInt64.hpp"

struct [[gnu::packed]] UIntPtr {
	using BackingType = uintptr_t;

	constexpr static BackingType Min = UINTPTR_MIN;
	constexpr static BackingType Max = UINTPTR_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	constexpr UIntPtr()
	    : value(0) {}
	constexpr UIntPtr(BackingType value)
	    : value(value) {}
	constexpr UIntPtr(UInt64 value)
	    : value(value.value) {}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}
	template <typename T>
	[[gnu::always_inline]] inline explicit operator T*() const {
		return reinterpret_cast<T*>(this->value);
	}

	// Arithmetic
	[[gnu::always_inline]] inline UIntPtr operator+(UIntPtr rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline UIntPtr operator-(UIntPtr rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline UIntPtr operator*(UIntPtr rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline UIntPtr operator/(UIntPtr rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline UIntPtr operator&(UIntPtr rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline UIntPtr operator|(UIntPtr rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline UIntPtr operator^(UIntPtr rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline UIntPtr operator<<(UIntPtr rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline UIntPtr operator>>(UIntPtr rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(UIntPtr rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(UIntPtr rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(UIntPtr rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(UIntPtr rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(UIntPtr rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(UIntPtr rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline UIntPtr& operator+=(const UIntPtr& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UIntPtr& operator-=(const UIntPtr& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UIntPtr& operator*=(const UIntPtr& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UIntPtr& operator/=(const UIntPtr& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline UIntPtr& operator&=(const UIntPtr& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UIntPtr& operator|=(const UIntPtr& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UIntPtr& operator^=(const UIntPtr& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline UIntPtr& operator<<=(const UIntPtr& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UIntPtr& operator>>=(const UIntPtr& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline UIntPtr  operator-() { return -this->value; }
	[[gnu::always_inline]] inline UIntPtr  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline UIntPtr& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline UIntPtr& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline UIntPtr operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline UIntPtr operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(UIntPtr) == 8);
