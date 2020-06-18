#pragma once

#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uintmax_t)) UInt {
	[[gnu::always_inline]] inline constexpr UInt()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr UInt(const uintmax_t& value)
	    : value(value) {}

	[[gnu::always_inline]] inline constexpr explicit operator uintmax_t()
	    const noexcept {
		return this->value;
	}

  private:
	uintmax_t value;
};
static_assert(sizeof(UInt) == sizeof(uintmax_t));
static_assert(alignof(UInt) == alignof(uintmax_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr UInt
operator+(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) + static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt
operator-(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) - static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt
operator*(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) * static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt
operator/(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) / static_cast<uintmax_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr UInt
operator&(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) & static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt
operator|(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) | static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt
operator^(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) ^ static_cast<uintmax_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr UInt
operator<<(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) << static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt
operator>>(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) >> static_cast<uintmax_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) < static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) > static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) <= static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) >= static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) == static_cast<uintmax_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const UInt& lhs, const UInt& rhs) noexcept {
	return static_cast<uintmax_t>(lhs) != static_cast<uintmax_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr UInt&
operator+=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt&
operator-=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt&
operator*=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt&
operator/=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr UInt&
operator&=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt&
operator|=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt&
operator^=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr UInt&
operator<<=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt&
operator>>=(UInt& lhs, const UInt& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr UInt
operator-(const UInt& value) noexcept {
	return -static_cast<uintmax_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt
operator~(const UInt& value) noexcept {
	return ~static_cast<uintmax_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt& operator++(UInt& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr UInt& operator--(UInt& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr UInt operator++(UInt& value,
                                                        int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr UInt operator--(UInt& value,
                                                        int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
