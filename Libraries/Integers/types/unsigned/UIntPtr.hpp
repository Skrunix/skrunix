#pragma once

#include <Integers/types/unsigned/UInt64.hpp>
#include <Integers/types/unsigned/USize.hpp>
#include <stdint.h>
#include <type_traits>

struct [[gnu::packed]] UIntPtr {
	using BackingType = uintptr_t;

	constexpr static BackingType Min = 0;
	constexpr static BackingType Max = UINTPTR_MAX;

	constexpr static int BitWidth = 64ull;

	BackingType value;

	const_inline UIntPtr()
	    : value(0) {}
	const_inline UIntPtr(const BackingType& value)
	    : value(value) {}
	const_inline UIntPtr(const UInt64& value)
	    : value(value.value) {}
	const_inline UIntPtr(const USize& value)
	    : value(value.value) {}

	// Pointer conversion
	template <typename T>
	const_inline static std::enable_if_t<std::is_pointer_v<T>, UIntPtr> From(
	    const T pointer) noexcept {
		return UIntPtr(reinterpret_cast<uintptr_t>(pointer));
	}

	template <typename T>
	const_inline std::enable_if_t<std::is_pointer_v<T>, T> To(USize offset = 0)
	    const noexcept {
		return reinterpret_cast<T>(this->value) + offset.value;
	}

	// Int conversion
	const_inline explicit operator BackingType() const noexcept {
		return this->value;
	}
	template <typename T>
	const_inline explicit operator T*() const noexcept {
		return reinterpret_cast<T*>(this->value);
	}

	// Arithmetic
	const_inline UIntPtr operator+(const UIntPtr& rhs) const noexcept {
		return this->value + rhs.value;
	};
	const_inline UIntPtr operator-(const UIntPtr& rhs) const noexcept {
		return this->value - rhs.value;
	};
	const_inline UIntPtr operator*(const UIntPtr& rhs) const noexcept {
		return this->value * rhs.value;
	};
	const_inline UIntPtr operator/(const UIntPtr& rhs) const noexcept {
		return this->value / rhs.value;
	};

	// Logical
	const_inline UIntPtr operator&(const UIntPtr& rhs) const noexcept {
		return this->value & rhs.value;
	};
	const_inline UIntPtr operator|(const UIntPtr& rhs) const noexcept {
		return this->value | rhs.value;
	};
	const_inline UIntPtr operator^(const UIntPtr& rhs) const noexcept {
		return this->value ^ rhs.value;
	};

	// Shift
	const_inline UIntPtr operator<<(const UIntPtr& rhs) const noexcept {
		return this->value << rhs.value;
	};
	const_inline UIntPtr operator>>(const UIntPtr& rhs) const noexcept {
		return this->value >> rhs.value;
	};

	// Comparison
	const_inline bool operator<(const UIntPtr& rhs) const noexcept {
		return this->value < rhs.value;
	};
	const_inline bool operator>(const UIntPtr& rhs) const noexcept {
		return this->value > rhs.value;
	};
	const_inline bool operator<=(const UIntPtr& rhs) const noexcept {
		return this->value <= rhs.value;
	};
	const_inline bool operator>=(const UIntPtr& rhs) const noexcept {
		return this->value >= rhs.value;
	};
	const_inline bool operator==(const UIntPtr& rhs) const noexcept {
		return this->value == rhs.value;
	};
	const_inline bool operator!=(const UIntPtr& rhs) const noexcept {
		return this->value != rhs.value;
	};

	// Arithmetic Assignment
	const_inline UIntPtr& operator+=(const UIntPtr& rhs) noexcept {
		this->value += rhs.value;
		return *this;
	};
	const_inline UIntPtr& operator-=(const UIntPtr& rhs) noexcept {
		this->value -= rhs.value;
		return *this;
	};
	const_inline UIntPtr& operator*=(const UIntPtr& rhs) noexcept {
		this->value *= rhs.value;
		return *this;
	};
	const_inline UIntPtr& operator/=(const UIntPtr& rhs) noexcept {
		this->value /= rhs.value;
		return *this;
	};

	// Logical Assignment
	const_inline UIntPtr& operator&=(const UIntPtr& rhs) noexcept {
		this->value &= rhs.value;
		return *this;
	};
	const_inline UIntPtr& operator|=(const UIntPtr& rhs) noexcept {
		this->value |= rhs.value;
		return *this;
	};
	const_inline UIntPtr& operator^=(const UIntPtr& rhs) noexcept {
		this->value ^= rhs.value;
		return *this;
	};

	// Shift Assignment
	const_inline UIntPtr& operator<<=(const UIntPtr& rhs) noexcept {
		this->value <<= rhs.value;
		return *this;
	};
	const_inline UIntPtr& operator>>=(const UIntPtr& rhs) noexcept {
		this->value >>= rhs.value;
		return *this;
	};

	// Prefix
	const_inline UIntPtr operator-() const noexcept { return -this->value; }
	const_inline UIntPtr operator~() const noexcept { return ~this->value; }
	const_inline UIntPtr& operator++() noexcept {
		++this->value;
		return *this;
	}
	const_inline UIntPtr& operator--() noexcept {
		--this->value;
		return *this;
	}

	// Postfix
	const_inline UIntPtr operator++(int) noexcept { return this->value++; }
	const_inline UIntPtr operator--(int) noexcept { return this->value--; }
};
static_assert(sizeof(UIntPtr) == 8);
