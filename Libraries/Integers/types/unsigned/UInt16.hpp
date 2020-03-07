#pragma once

#include <Integers/types/unsigned/UInt8.hpp>
#include <stdint.h>

struct [[gnu::packed]] UInt16 {
	using BackingType = uint16_t;

	constexpr static BackingType Min = UINT16_MIN;
	constexpr static BackingType Max = UINT16_MAX;

	constexpr static int         BitWidth = 16u;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	const_inline UInt16()
	    : value(0) {}
	const_inline UInt16(const BackingType& value)
	    : value(value) {}

	const_inline UInt8 low() const noexcept { return this->value & HalfMask; }
	const_inline UInt8 high() const noexcept {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	const_inline explicit operator BackingType() const noexcept {
		return this->value;
	}

	// Arithmetic
	const_inline UInt16 operator+(const UInt16& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline UInt16 operator-(const UInt16& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline UInt16 operator*(const UInt16& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline UInt16 operator/(const UInt16& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline UInt16 operator&(const UInt16& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline UInt16 operator|(const UInt16& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline UInt16 operator^(const UInt16& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline UInt16 operator<<(const UInt16& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline UInt16 operator>>(const UInt16& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const UInt16& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const UInt16& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const UInt16& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const UInt16& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const UInt16& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const UInt16& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline UInt16& operator+=(const UInt16& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline UInt16& operator-=(const UInt16& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline UInt16& operator*=(const UInt16& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline UInt16& operator/=(const UInt16& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline UInt16& operator&=(const UInt16& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline UInt16& operator|=(const UInt16& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline UInt16& operator^=(const UInt16& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline UInt16& operator<<=(const UInt16& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline UInt16& operator>>=(const UInt16& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline UInt16 operator-() const noexcept { return -this->value; }
	const_inline UInt16 operator~() const noexcept { return ~this->value; }
	const_inline UInt16& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline UInt16& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline UInt16 operator++(int) noexcept { return this->value++; }
	const_inline UInt16 operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(UInt16) == 2);
