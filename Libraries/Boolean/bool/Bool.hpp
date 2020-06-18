#pragma once

struct [[gnu::packed]] alignas(alignof(bool)) Bool {
	Bool()    = delete;
	Bool(int) = delete;

	[[gnu::always_inline]] inline constexpr Bool(bool value) noexcept
	    : value(value){};

	[[gnu::always_inline]] inline constexpr explicit operator bool()
	    const noexcept {
		return this->value;
	}

  private:
	bool value;
};
static_assert(sizeof(Bool) == sizeof(bool));
static_assert(alignof(Bool) == alignof(bool));

[[gnu::always_inline]] inline constexpr Bool
operator!(const Bool& value) noexcept {
	return !static_cast<bool>(value);
}

[[gnu::always_inline]] inline constexpr Bool
operator==(const Bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) == static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator!=(const Bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) != static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator&&(const Bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) && static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator||(const Bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) || static_cast<bool>(rhs);
}

[[gnu::always_inline]] inline constexpr Bool
operator==(const Bool& lhs, const bool& rhs) noexcept {
	return static_cast<bool>(lhs) == static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator!=(const Bool& lhs, const bool& rhs) noexcept {
	return static_cast<bool>(lhs) != static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator&&(const Bool& lhs, const bool& rhs) noexcept {
	return static_cast<bool>(lhs) && static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator||(const Bool& lhs, const bool& rhs) noexcept {
	return static_cast<bool>(lhs) || static_cast<bool>(rhs);
}

[[gnu::always_inline]] inline constexpr Bool
operator==(const bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) == static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator!=(const bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) != static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator&&(const bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) && static_cast<bool>(rhs);
}
[[gnu::always_inline]] inline constexpr Bool
operator||(const bool& lhs, const Bool& rhs) noexcept {
	return static_cast<bool>(lhs) || static_cast<bool>(rhs);
}
