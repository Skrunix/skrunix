#pragma once

#include <type_trait/bool_constant.hpp>
#include <type_trait/conjunction.hpp>
#include <type_trait/declval.hpp>
#include <type_trait/is_void.hpp>

namespace std {

template <class From, class To>
struct is_nothrow_convertible
    : std::conjunction<std::is_void<From>, std::is_void<To>> {};

template <class From, class To>
requires requires {
	static_cast<To (*)()>(nullptr);
	{ std::declval<void (&)(To) noexcept>()(std::declval<From>()) }
	noexcept;
}
struct is_nothrow_convertible<From, To> : std::true_type {};

template <class From, class To>
inline constexpr bool is_nothrow_convertible_v =
    is_nothrow_convertible<From, To>::value;

} // namespace std
