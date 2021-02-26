#pragma once

#include <concept/same_as.hpp>
#include <type_trait/is_nothrow_convertible.hpp>

struct [[gnu::packed]] alignas(alignof(bool)) Bool {
  private:
	bool value;

	struct P_ {
		bool V_;
	};
	typedef const bool P_::*bool_;

  public:
	[[gnu::always_inline]] inline constexpr Bool(const Bool& b) noexcept
	    : value(b.value) {}

	template <std::same_as<bool> B>
	[[gnu::always_inline]] inline constexpr Bool(const B b) noexcept
	    : value(static_cast<bool>(b)) {}

	[[gnu::always_inline]] inline constexpr operator bool_() const noexcept {
		return this->value ? &P_::V_ : 0;
	}
};

[[gnu::always_inline]] inline constexpr Bool
operator!(const Bool& value) noexcept {
	return Bool(!static_cast<bool>(value));
}

[[gnu::always_inline]] inline constexpr Bool
operator==(const Bool& lhs, const Bool& rhs) noexcept {
	return Bool(static_cast<bool>(lhs) == static_cast<bool>(rhs));
}

[[gnu::always_inline]] inline constexpr Bool
operator!=(const Bool& lhs, const Bool& rhs) noexcept {
	return Bool(static_cast<bool>(lhs) != static_cast<bool>(rhs));
}

// Size and Alignment
static_assert(sizeof(Bool) == sizeof(bool));
static_assert(alignof(Bool) == alignof(bool));

// Constructor
static_assert(Bool(true));

// Negation
static_assert(!Bool(true) == false);
static_assert(!Bool(false) == true);

// Equality
static_assert(Bool(true) == true);
static_assert(Bool(false) == false);
static_assert(Bool(true) == Bool(true));
static_assert(Bool(false) == Bool(false));

// Inequality
static_assert(Bool(true) != false);
static_assert(Bool(false) != true);
static_assert(Bool(true) != Bool(false));
static_assert(Bool(false) != Bool(true));

// Conversion to and from bool
static_assert(std::is_nothrow_convertible_v<bool, Bool>);
static_assert(std::is_nothrow_convertible_v<Bool, bool>);

// Conversion to and from int, float, void*
static_assert(!std::is_nothrow_convertible_v<int, Bool>);
static_assert(!std::is_nothrow_convertible_v<Bool, int>);
static_assert(!std::is_nothrow_convertible_v<float, Bool>);
static_assert(!std::is_nothrow_convertible_v<Bool, float>);
static_assert(!std::is_nothrow_convertible_v<void*, Bool>);
static_assert(!std::is_nothrow_convertible_v<Bool, void*>);
