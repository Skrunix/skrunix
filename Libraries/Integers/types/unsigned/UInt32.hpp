#pragma once

#include <Integers/types/unsigned/UInt16.hpp>
#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uint32_t)) UInt32 {
	[[gnu::always_inline]] inline constexpr UInt32()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr UInt32(const uint32_t& value)
	    : value(value) {}
	[[gnu::always_inline]] inline constexpr UInt32(const UInt8& value)
	    : value(static_cast<uint8_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UInt32(const UInt16& value)
	    : value(static_cast<uint16_t>(value)) {}

	[[gnu::always_inline]] inline constexpr explicit operator uint32_t()
	    const noexcept {
		return this->value;
	}

	[[gnu::always_inline]] inline constexpr UInt16 low() const noexcept {
		return this->value & 0xFFFF;
	}
	[[gnu::always_inline]] inline constexpr UInt16 high() const noexcept {
		return (this->value >> 16) & 0xFFFF;
	}

  private:
	uint32_t value;
};
static_assert(sizeof(UInt32) == sizeof(uint32_t));
static_assert(alignof(UInt32) == alignof(uint32_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr UInt32
operator+(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) + static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt32
operator-(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) - static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt32
operator*(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) * static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt32
operator/(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) / static_cast<uint32_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr UInt32
operator&(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt32
operator|(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt32
operator^(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) ^ static_cast<uint32_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr UInt32
operator<<(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) << static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt32
operator>>(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) >> static_cast<uint32_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) <= static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) >= static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const UInt32& lhs, const UInt32& rhs) noexcept {
	return static_cast<uint32_t>(lhs) != static_cast<uint32_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr UInt32&
operator+=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt32&
operator-=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt32&
operator*=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt32&
operator/=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr UInt32&
operator&=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt32&
operator|=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt32&
operator^=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr UInt32&
operator<<=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt32&
operator>>=(UInt32& lhs, const UInt32& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr UInt32
operator-(const UInt32& value) noexcept {
	return -static_cast<uint32_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt32
operator~(const UInt32& value) noexcept {
	return ~static_cast<uint32_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt32&
operator++(UInt32& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr UInt32&
operator--(UInt32& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr UInt32 operator++(UInt32& value,
                                                          int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr UInt32 operator--(UInt32& value,
                                                          int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
