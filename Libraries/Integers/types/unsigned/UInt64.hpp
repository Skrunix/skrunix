#pragma once

#include "UInt32.hpp"
#include "USize.hpp"

struct [[gnu::packed]] UInt64 {
	using BackingType = uint64_t;

	constexpr static BackingType Min = UINT64_MIN;
	constexpr static BackingType Max = UINT64_MAX;

	constexpr static int         BitWidth = 64ull;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	constexpr UInt64()
	    : value(0) {}
	constexpr UInt64(BackingType value)
	    : value(value) {}
	constexpr UInt64(USize value)
	    : value(value.value) {}

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
	[[gnu::always_inline]] inline UInt64 operator+(UInt64 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline UInt64 operator-(UInt64 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline UInt64 operator*(UInt64 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline UInt64 operator/(UInt64 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline UInt64 operator&(UInt64 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline UInt64 operator|(UInt64 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline UInt64 operator^(UInt64 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline UInt64 operator<<(UInt64 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline UInt64 operator>>(UInt64 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(UInt64 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(UInt64 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(UInt64 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(UInt64 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(UInt64 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(UInt64 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline UInt64& operator+=(const UInt64& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt64& operator-=(const UInt64& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt64& operator*=(const UInt64& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt64& operator/=(const UInt64& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline UInt64& operator&=(const UInt64& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt64& operator|=(const UInt64& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt64& operator^=(const UInt64& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline UInt64& operator<<=(const UInt64& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt64& operator>>=(const UInt64& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline UInt64  operator-() { return -this->value; }
	[[gnu::always_inline]] inline UInt64  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline UInt64& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline UInt64& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline UInt64 operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline UInt64 operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(UInt64) == 8);
