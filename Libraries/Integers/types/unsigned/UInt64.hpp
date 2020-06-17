#pragma once

#include <Integers/types/unsigned/UInt32.hpp>
#include <Integers/types/unsigned/USize.hpp>
#include <stdint.h>

struct [[gnu::packed]] UInt64 {
	using BackingType = uint64_t;

	constexpr static BackingType Min = 0;
	constexpr static BackingType Max = UINT64_MAX;

	constexpr static int         BitWidth = 64ull;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	const_inline UInt64()
	    : value(0) {}
	const_inline UInt64(const BackingType& value)
	    : value(value) {}
	const_inline UInt64(const UInt8& value)
	    : value(value.value) {}
	const_inline UInt64(const USize& value)
	    : value(value.value) {}

	const_inline UInt32 low() const noexcept { return this->value & HalfMask; }
	const_inline UInt32 high() const noexcept {
		return (this->value >> (BitWidth / 2)) & HalfMask;
	}

	// Int conversion
	const_inline explicit operator BackingType() const noexcept {
		return this->value;
	}

	// Arithmetic
	const_inline UInt64 operator+(const UInt64& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline UInt64 operator-(const UInt64& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline UInt64 operator*(const UInt64& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline UInt64 operator/(const UInt64& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline UInt64 operator&(const UInt64& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline UInt64 operator|(const UInt64& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline UInt64 operator^(const UInt64& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline UInt64 operator<<(const UInt64& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline UInt64 operator>>(const UInt64& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const UInt64& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const UInt64& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const UInt64& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const UInt64& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const UInt64& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const UInt64& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline UInt64& operator+=(const UInt64& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline UInt64& operator-=(const UInt64& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline UInt64& operator*=(const UInt64& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline UInt64& operator/=(const UInt64& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline UInt64& operator&=(const UInt64& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline UInt64& operator|=(const UInt64& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline UInt64& operator^=(const UInt64& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline UInt64& operator<<=(const UInt64& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline UInt64& operator>>=(const UInt64& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline UInt64 operator-() const noexcept { return -this->value; }
	const_inline UInt64 operator~() const noexcept { return ~this->value; }
	const_inline UInt64& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline UInt64& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline UInt64 operator++(int) noexcept { return this->value++; }
	const_inline UInt64 operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(UInt64) == 8);
