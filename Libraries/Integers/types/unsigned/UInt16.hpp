#pragma once

#include <Integers/types/unsigned/UInt8.hpp>
#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uint16_t)) UInt16 {
	[[gnu::always_inline]] inline constexpr UInt16()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr UInt16(const uint16_t& value)
	    : value(value) {}
	[[gnu::always_inline]] inline constexpr UInt16(const UInt8& value)
	    : value(static_cast<uint8_t>(value)) {}

	[[gnu::always_inline]] inline constexpr explicit operator uint16_t()
	    const noexcept {
		return this->value;
	}

	[[gnu::always_inline]] inline constexpr UInt8 low() const noexcept {
		return this->value & 0xFF;
	}
	[[gnu::always_inline]] inline constexpr UInt8 high() const noexcept {
		return (this->value >> 8) & 0xFF;
	}

  private:
	uint16_t value;
};
static_assert(sizeof(UInt16) == sizeof(uint16_t));
static_assert(alignof(UInt16) == alignof(uint16_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr UInt16
operator+(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) + static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt16
operator-(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) - static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt16
operator*(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) * static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt16
operator/(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) / static_cast<uint16_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr UInt16
operator&(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) & static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt16
operator|(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) | static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt16
operator^(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) ^ static_cast<uint16_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr UInt16
operator<<(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) << static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt16
operator>>(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) >> static_cast<uint16_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) < static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) > static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) <= static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) >= static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) == static_cast<uint16_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const UInt16& lhs, const UInt16& rhs) noexcept {
	return static_cast<uint16_t>(lhs) != static_cast<uint16_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr UInt16&
operator+=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt16&
operator-=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt16&
operator*=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt16&
operator/=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr UInt16&
operator&=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt16&
operator|=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt16&
operator^=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr UInt16&
operator<<=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt16&
operator>>=(UInt16& lhs, const UInt16& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr UInt16
operator-(const UInt16& value) noexcept {
	return -static_cast<uint16_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt16
operator~(const UInt16& value) noexcept {
	return ~static_cast<uint16_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt16&
operator++(UInt16& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr UInt16&
operator--(UInt16& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr UInt16 operator++(UInt16& value,
                                                          int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr UInt16 operator--(UInt16& value,
                                                          int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
