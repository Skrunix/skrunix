#pragma once

#include <Integers/types/unsigned/UInt32.hpp>
#include <stdint.h>

struct [[gnu::packed]] alignas(alignof(uint64_t)) UInt64 {
	[[gnu::always_inline]] inline constexpr UInt64()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr UInt64(const uint64_t& value)
	    : value(value) {}
	[[gnu::always_inline]] inline constexpr UInt64(const UInt8& value)
	    : value(static_cast<uint8_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UInt64(const UInt16& value)
	    : value(static_cast<uint16_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UInt64(const UInt32& value)
	    : value(static_cast<uint32_t>(value)) {}

	[[gnu::always_inline]] inline constexpr explicit operator uint64_t()
	    const noexcept {
		return this->value;
	}

	[[gnu::always_inline]] inline constexpr UInt32 low() const noexcept {
		return this->value & 0xFFFFFFFF;
	}
	[[gnu::always_inline]] inline constexpr UInt32 high() const noexcept {
		return (this->value >> 32) & 0xFFFFFFFF;
	}

  private:
	uint64_t value;
};
static_assert(sizeof(UInt64) == sizeof(uint64_t));
static_assert(alignof(UInt64) == alignof(uint64_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr UInt64
operator+(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) + static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt64
operator-(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) - static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt64
operator*(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) * static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt64
operator/(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) / static_cast<uint64_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr UInt64
operator&(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) & static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt64
operator|(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) | static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt64
operator^(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) ^ static_cast<uint64_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr UInt64
operator<<(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) << static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UInt64
operator>>(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) >> static_cast<uint64_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) <= static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) >= static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) == static_cast<uint64_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const UInt64& lhs, const UInt64& rhs) noexcept {
	return static_cast<uint64_t>(lhs) != static_cast<uint64_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr UInt64&
operator+=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt64&
operator-=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt64&
operator*=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt64&
operator/=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr UInt64&
operator&=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt64&
operator|=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt64&
operator^=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr UInt64&
operator<<=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UInt64&
operator>>=(UInt64& lhs, const UInt64& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr UInt64
operator-(const UInt64& value) noexcept {
	return -static_cast<uint64_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt64
operator~(const UInt64& value) noexcept {
	return ~static_cast<uint64_t>(value);
}
[[gnu::always_inline]] inline constexpr UInt64&
operator++(UInt64& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr UInt64&
operator--(UInt64& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr UInt64 operator++(UInt64& value,
                                                          int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr UInt64 operator--(UInt64& value,
                                                          int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
