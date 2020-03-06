#pragma once

#include <stdint.h>

struct [[gnu::packed]] USize {
	using BackingType = size_t;

	constexpr static BackingType Min = SIZE_MIN;
	constexpr static BackingType Max = SIZE_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	const_inline USize()
	    : value(0) {}
	const_inline USize(const BackingType& value)
	    : value(value) {}

	// Int conversion
	const_inline explicit operator BackingType() const noexcept {
		return this->value;
	}

	// Arithmetic
	const_inline USize operator+(const USize& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline USize operator-(const USize& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline USize operator*(const USize& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline USize operator/(const USize& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline USize operator&(const USize& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline USize operator|(const USize& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline USize operator^(const USize& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline USize operator<<(const USize& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline USize operator>>(const USize& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const USize& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const USize& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const USize& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const USize& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const USize& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const USize& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline USize& operator+=(const USize& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline USize& operator-=(const USize& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline USize& operator*=(const USize& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline USize& operator/=(const USize& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline USize& operator&=(const USize& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline USize& operator|=(const USize& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline USize& operator^=(const USize& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline USize& operator<<=(const USize& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline USize& operator>>=(const USize& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline USize operator-() const noexcept { return -this->value; }
	const_inline USize operator~() const noexcept { return ~this->value; }
	const_inline USize& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline USize& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline USize operator++(int) noexcept { return this->value++; }
	const_inline USize operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(USize) == 8);
