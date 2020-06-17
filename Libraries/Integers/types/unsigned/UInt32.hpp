#pragma once

#include <Integers/types/unsigned/UInt16.hpp>
#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uint32_t)) UInt32 {
	using BackingType = uint32_t;

	constexpr static BackingType Min = 0;
	constexpr static BackingType Max = UINT32_MAX;

	constexpr static int         BitWidth = 32ul;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	const_inline UInt32()
	    : value(0) {}
	const_inline UInt32(const BackingType& value)
	    : value(value) {}

	const_inline UInt16 low() const noexcept { return this->value & HalfMask; }
	const_inline UInt16 high() const noexcept {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	const_inline explicit operator BackingType() const noexcept {
		return this->value;
	}

	// Arithmetic
	const_inline UInt32 operator+(const UInt32& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline UInt32 operator-(const UInt32& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline UInt32 operator*(const UInt32& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline UInt32 operator/(const UInt32& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline UInt32 operator&(const UInt32& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline UInt32 operator|(const UInt32& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline UInt32 operator^(const UInt32& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline UInt32 operator<<(const UInt32& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline UInt32 operator>>(const UInt32& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const UInt32& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const UInt32& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const UInt32& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const UInt32& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const UInt32& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const UInt32& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline UInt32& operator+=(const UInt32& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline UInt32& operator-=(const UInt32& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline UInt32& operator*=(const UInt32& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline UInt32& operator/=(const UInt32& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline UInt32& operator&=(const UInt32& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline UInt32& operator|=(const UInt32& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline UInt32& operator^=(const UInt32& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline UInt32& operator<<=(const UInt32& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline UInt32& operator>>=(const UInt32& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline UInt32 operator-() const noexcept { return -this->value; }
	const_inline UInt32 operator~() const noexcept { return ~this->value; }
	const_inline UInt32& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline UInt32& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline UInt32 operator++(int) noexcept { return this->value++; }
	const_inline UInt32 operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(UInt32) == sizeof(uint32_t));
static_assert(alignof(UInt32) == alignof(uint32_t));
