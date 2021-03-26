#pragma once

#include <Integers/types/unsigned/UInt32.hpp>
#include <stddef.h>

struct [[gnu::packed]] alignas(alignof(size_t)) USize {
	[[gnu::always_inline]] inline constexpr USize()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr USize(const size_t& value)
	    : value(value) {}
	[[gnu::always_inline]] inline constexpr USize(const UInt8& value)
	    : value(static_cast<uint8_t>(value)) {}
	[[gnu::always_inline]] inline constexpr USize(const UInt16& value)
	    : value(static_cast<uint16_t>(value)) {}
	[[gnu::always_inline]] inline constexpr USize(const UInt32& value)
	    : value(static_cast<uint32_t>(value)) {}

	[[gnu::always_inline]] inline constexpr explicit operator size_t()
	    const noexcept {
		return this->value;
	}

  private:
	size_t value;
};
static_assert(sizeof(USize) == sizeof(size_t));
static_assert(alignof(USize) == alignof(size_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr USize
operator+(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) + static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr USize
operator-(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) - static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr USize
operator*(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) * static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr USize
operator/(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) / static_cast<size_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr USize
operator&(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) & static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr USize
operator|(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) | static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr USize
operator^(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) ^ static_cast<size_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr USize
operator<<(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) << static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr USize
operator>>(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) >> static_cast<size_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) < static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) > static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) <= static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) >= static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) == static_cast<size_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const USize& lhs, const USize& rhs) noexcept {
	return static_cast<size_t>(lhs) != static_cast<size_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr USize&
operator+=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr USize&
operator-=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr USize&
operator*=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr USize&
operator/=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr USize&
operator&=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr USize&
operator|=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr USize&
operator^=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr USize&
operator<<=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr USize&
operator>>=(USize& lhs, const USize& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr USize
operator-(const USize& value) noexcept {
	return -static_cast<size_t>(value);
}
[[gnu::always_inline]] inline constexpr USize
operator~(const USize& value) noexcept {
	return ~static_cast<size_t>(value);
}
[[gnu::always_inline]] inline constexpr USize&
operator++(USize& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr USize&
operator--(USize& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr USize operator++(USize& value,
                                                         int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr USize operator--(USize& value,
                                                         int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
