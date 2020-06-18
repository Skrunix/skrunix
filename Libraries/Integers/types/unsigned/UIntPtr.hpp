#pragma once

#include <Integers/types/unsigned/UInt64.hpp>
#include <Integers/types/unsigned/USize.hpp>
#include <stdint.h>
#include <type_traits>

template <typename T>
concept PointerType = std::is_pointer_v<T>;

struct [[gnu::packed]] alignas(alignof(uintptr_t)) UIntPtr {
	[[gnu::always_inline]] inline constexpr UIntPtr()
	    : value(0) {}
	[[gnu::always_inline]] inline constexpr UIntPtr(const uintptr_t& value)
	    : value(value) {}
	[[gnu::always_inline]] inline constexpr UIntPtr(const UInt8& value)
	    : value(static_cast<uint8_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UIntPtr(const UInt16& value)
	    : value(static_cast<uint16_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UIntPtr(const UInt32& value)
	    : value(static_cast<uint32_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UIntPtr(const UInt64& value)
	    : value(static_cast<uint64_t>(value)) {}
	[[gnu::always_inline]] inline constexpr UIntPtr(const USize& value)
	    : value(static_cast<size_t>(value)) {}

	[[gnu::always_inline]] inline constexpr explicit operator uintptr_t()
	    const noexcept {
		return this->value;
	}

	// Pointer conversion
	template <PointerType T>
	[[gnu::always_inline]] inline constexpr static UIntPtr From(
	    const T pointer) noexcept {
		return UIntPtr(reinterpret_cast<uintptr_t>(pointer));
	}

	template <PointerType T>
	[[gnu::always_inline]] inline constexpr T To(USize offset = 0)
	    const noexcept {
		return reinterpret_cast<T>(this->value) +
		       static_cast<ptrdiff_t>(static_cast<size_t>(offset));
	}

  private:
	uintptr_t value;
};
static_assert(sizeof(UIntPtr) == sizeof(uintptr_t));
static_assert(alignof(UIntPtr) == alignof(uintptr_t));

// Arithmetic
[[gnu::always_inline]] inline constexpr UIntPtr
operator+(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) + static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UIntPtr
operator-(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) - static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UIntPtr
operator*(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) * static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UIntPtr
operator/(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) / static_cast<uintptr_t>(rhs);
};

// Logical
[[gnu::always_inline]] inline constexpr UIntPtr
operator&(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) & static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UIntPtr
operator|(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) | static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UIntPtr
operator^(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) ^ static_cast<uintptr_t>(rhs);
};

// Shift
[[gnu::always_inline]] inline constexpr UIntPtr
operator<<(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) << static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr UIntPtr
operator>>(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) >> static_cast<uintptr_t>(rhs);
};

// Comparison
[[gnu::always_inline]] inline constexpr bool
operator<(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) < static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) > static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator<=(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) <= static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator>=(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) >= static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator==(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) == static_cast<uintptr_t>(rhs);
};
[[gnu::always_inline]] inline constexpr bool
operator!=(const UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	return static_cast<uintptr_t>(lhs) != static_cast<uintptr_t>(rhs);
};

// Arithmetic Assignment
[[gnu::always_inline]] inline constexpr UIntPtr&
operator+=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UIntPtr&
operator-=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UIntPtr&
operator*=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UIntPtr&
operator/=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
};

// Logical Assignment
[[gnu::always_inline]] inline constexpr UIntPtr&
operator&=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UIntPtr&
operator|=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UIntPtr&
operator^=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
};

// Shift Assignment
[[gnu::always_inline]] inline constexpr UIntPtr&
operator<<=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs << rhs;
	return lhs;
};
[[gnu::always_inline]] inline constexpr UIntPtr&
operator>>=(UIntPtr& lhs, const UIntPtr& rhs) noexcept {
	lhs = lhs >> rhs;
	return lhs;
};

// Prefix
[[gnu::always_inline]] inline constexpr UIntPtr
operator-(const UIntPtr& value) noexcept {
	return -static_cast<uintptr_t>(value);
}
[[gnu::always_inline]] inline constexpr UIntPtr
operator~(const UIntPtr& value) noexcept {
	return ~static_cast<uintptr_t>(value);
}
[[gnu::always_inline]] inline constexpr UIntPtr&
operator++(UIntPtr& value) noexcept {
	value += 1;
	return value;
}
[[gnu::always_inline]] inline constexpr UIntPtr&
operator--(UIntPtr& value) noexcept {
	value -= 1;
	return value;
}

// Postfix
[[gnu::always_inline]] inline constexpr UIntPtr operator++(UIntPtr& value,
                                                           int) noexcept {
	auto copy = value;
	value += 1;
	return copy;
}
[[gnu::always_inline]] inline constexpr UIntPtr operator--(UIntPtr& value,
                                                           int) noexcept {
	auto copy = value;
	value -= 1;
	return copy;
}
