#pragma once

#include "UInt16.hpp"

struct [[gnu::packed]] UInt32 {
	using BackingType = uint32_t;

	constexpr static BackingType Min = UINT32_MIN;
	constexpr static BackingType Max = UINT32_MAX;

	constexpr static int BitWidth = 32ul;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	constexpr UInt32()
	    : value(0) {}
	constexpr UInt32(BackingType value)
	    : value(value) {}

	[[gnu::always_inline]] inline UInt16 low() {
		return this->value & HalfMask;
	}
	[[gnu::always_inline]] inline UInt16 high() {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	[[gnu::always_inline]] inline explicit operator BackingType() const {
		return this->value;
	}

	// Arithmetic
	[[gnu::always_inline]] inline UInt32 operator+(UInt32 rhs) {
		return this->value + rhs.value;
	};
	[[gnu::always_inline]] inline UInt32 operator-(UInt32 rhs) {
		return this->value - rhs.value;
	};
	[[gnu::always_inline]] inline UInt32 operator*(UInt32 rhs) {
		return this->value * rhs.value;
	};
	[[gnu::always_inline]] inline UInt32 operator/(UInt32 rhs) {
		return this->value / rhs.value;
	};

	// Logical
	[[gnu::always_inline]] inline UInt32 operator&(UInt32 rhs) {
		return this->value & rhs.value;
	};
	[[gnu::always_inline]] inline UInt32 operator|(UInt32 rhs) {
		return this->value | rhs.value;
	};
	[[gnu::always_inline]] inline UInt32 operator^(UInt32 rhs) {
		return this->value ^ rhs.value;
	};

	// Shift
	[[gnu::always_inline]] inline UInt32 operator<<(UInt32 rhs) {
		return this->value << rhs.value;
	};
	[[gnu::always_inline]] inline UInt32 operator>>(UInt32 rhs) {
		return this->value >> rhs.value;
	};

	// Comparison
	[[gnu::always_inline]] inline bool operator<(UInt32 rhs) {
		return this->value < rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>(UInt32 rhs) {
		return this->value > rhs.value;
	};
	[[gnu::always_inline]] inline bool operator<=(UInt32 rhs) {
		return this->value <= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator>=(UInt32 rhs) {
		return this->value >= rhs.value;
	};
	[[gnu::always_inline]] inline bool operator==(UInt32 rhs) {
		return this->value == rhs.value;
	};
	[[gnu::always_inline]] inline bool operator!=(UInt32 rhs) {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	[[gnu::always_inline]] inline UInt32& operator+=(const UInt32& rhs) {
		this->value += rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt32& operator-=(const UInt32& rhs) {
		this->value -= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt32& operator*=(const UInt32& rhs) {
		this->value *= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt32& operator/=(const UInt32& rhs) {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	[[gnu::always_inline]] inline UInt32& operator&=(const UInt32& rhs) {
		this->value &= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt32& operator|=(const UInt32& rhs) {
		this->value |= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt32& operator^=(const UInt32& rhs) {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	[[gnu::always_inline]] inline UInt32& operator<<=(const UInt32& rhs) {
		this->value <<= rhs.value;
		return *this;
	};
	[[gnu::always_inline]] inline UInt32& operator>>=(const UInt32& rhs) {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	[[gnu::always_inline]] inline UInt32  operator-() { return -this->value; }
	[[gnu::always_inline]] inline UInt32  operator~() { return ~this->value; }
	[[gnu::always_inline]] inline UInt32& operator++() {
		++this->value;
		return *this;
	}
	[[gnu::always_inline]] inline UInt32& operator--() {
		--this->value;
		return *this;
	}

	// Postfix
	[[gnu::always_inline]] inline UInt32 operator++(int) {
		return this->value++;
	}
	[[gnu::always_inline]] inline UInt32 operator--(int) {
		return this->value--;
	}
};
static_assert(sizeof(UInt32) == 4);
