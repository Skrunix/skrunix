#pragma once

#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uint8_t)) UInt8 {
	using BackingType = uint8_t;

	constexpr static BackingType Min = 0;
	constexpr static BackingType Max = UINT8_MAX;

	constexpr static int         BitWidth = 8u;
	constexpr static BackingType HalfMask = Max >> (BitWidth / 2);

	BackingType value;

	const_inline UInt8()
	    : value(0) {}
	const_inline UInt8(const BackingType& value)
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
	const_inline UInt8 operator+(const UInt8& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline UInt8 operator-(const UInt8& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline UInt8 operator*(const UInt8& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline UInt8 operator/(const UInt8& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline UInt8 operator&(const UInt8& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline UInt8 operator|(const UInt8& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline UInt8 operator^(const UInt8& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline UInt8 operator<<(const UInt8& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline UInt8 operator>>(const UInt8& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const UInt8& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const UInt8& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const UInt8& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const UInt8& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const UInt8& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const UInt8& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline UInt8& operator+=(const UInt8& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline UInt8& operator-=(const UInt8& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline UInt8& operator*=(const UInt8& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline UInt8& operator/=(const UInt8& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline UInt8& operator&=(const UInt8& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline UInt8& operator|=(const UInt8& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline UInt8& operator^=(const UInt8& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline UInt8& operator<<=(const UInt8& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline UInt8& operator>>=(const UInt8& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline UInt8 operator-() const noexcept { return -this->value; }
	const_inline UInt8 operator~() const noexcept { return ~this->value; }
	const_inline UInt8& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline UInt8& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline UInt8 operator++(int) noexcept { return this->value++; }
	const_inline UInt8 operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(UInt8) == sizeof(uint8_t));
static_assert(alignof(UInt8) == alignof(uint8_t));
