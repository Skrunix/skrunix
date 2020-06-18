#pragma once

#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uint8_t)) UInt8 {
	[[gnu::always_inline]] inline constexpr UInt8()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr UInt8(const uint8_t& value)
	    : value(value) {}

	[[gnu::always_inline]] inline constexpr explicit operator uint8_t()
	    const noexcept {
		return this->value;
	}

	[[gnu::always_inline]] inline constexpr UInt8 low() const noexcept {
		return this->value & 0xF;
	}
	[[gnu::always_inline]] inline constexpr UInt8 high() const noexcept {
		return (this->value >> 4) & 0xF;
	}

  private:
	uint8_t value;
};
static_assert(sizeof(UInt8) == sizeof(uint8_t));
static_assert(alignof(UInt8) == alignof(uint8_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr UInt8
operator+(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) + static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt8
operator-(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) - static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt8
operator*(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) * static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt8
operator/(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) / static_cast<uint8_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr UInt8
operator&(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt8
operator|(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt8
operator^(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr UInt8
operator<<(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) << static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt8
operator>>(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) >> static_cast<uint8_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) < static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) > static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) <= static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) >= static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const UInt8& lhs, const UInt8& rhs) noexcept {
	return static_cast<uint8_t>(lhs) != static_cast<uint8_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr UInt8&
operator+=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt8&
operator-=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt8&
operator*=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt8&
operator/=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr UInt8&
operator&=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt8&
operator|=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt8&
operator^=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr UInt8&
operator<<=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt8&
operator>>=(UInt8& lhs, const UInt8& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr UInt8
operator-(const UInt8& value) noexcept {
	return -static_cast<uint8_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt8
operator~(const UInt8& value) noexcept {
	return ~static_cast<uint8_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt8&
operator++(UInt8& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr UInt8&
operator--(UInt8& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr UInt8 operator++(UInt8& value,
                                                         int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr UInt8 operator--(UInt8& value,
                                                         int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
