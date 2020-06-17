#pragma once

#include <Integers/types/unsigned/UInt32.hpp>
#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uintmax_t)) UInt {
	using BackingType = uintmax_t;

	constexpr static BackingType Min = 0;
	constexpr static BackingType Max = UINTMAX_MAX;

	constexpr static int         BitWidth = 64ull;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	constexpr UInt()
	    : value(0) {}
	constexpr UInt(const BackingType& value)
	    : value(value) {}

	const_inline UInt32 low() const noexcept { return this->value & HalfMask; }
	const_inline UInt32 high() const noexcept {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	const_inline explicit operator BackingType() const noexcept {
		return this->value;
	}

	// Arithmetic
	const_inline UInt operator+(const UInt& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline UInt operator-(const UInt& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline UInt operator*(const UInt& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline UInt operator/(const UInt& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline UInt operator&(const UInt& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline UInt operator|(const UInt& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline UInt operator^(const UInt& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline UInt operator<<(const UInt& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline UInt operator>>(const UInt& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const UInt& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const UInt& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const UInt& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const UInt& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const UInt& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const UInt& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline UInt& operator+=(const UInt& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline UInt& operator-=(const UInt& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline UInt& operator*=(const UInt& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline UInt& operator/=(const UInt& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline UInt& operator&=(const UInt& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline UInt& operator|=(const UInt& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline UInt& operator^=(const UInt& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline UInt& operator<<=(const UInt& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline UInt& operator>>=(const UInt& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline UInt operator-() const noexcept { return -this->value; }
	const_inline UInt operator~() const noexcept { return ~this->value; }
	const_inline UInt& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline UInt& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline UInt operator++(int) noexcept { return this->value++; }
	const_inline UInt operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(UInt) == sizeof(uintmax_t));
static_assert(alignof(UInt) == alignof(uintmax_t));
