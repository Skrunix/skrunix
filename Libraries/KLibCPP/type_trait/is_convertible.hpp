#pragma once

#include <type_trait/bool_constant.hpp>
#include <type_trait/declval.hpp>
#include <type_trait/is_void.hpp>

namespace std {

namespace detail {

template <class T>
auto test_returnable(int)
    -> decltype(void(static_cast<T (*)()>(nullptr)), std::true_type{});
template <class>
auto test_returnable(...) -> std::false_type;

template <class From, class To>
auto test_implicitly_convertible(int)
    -> decltype(void(std::declval<void (&)(To)>()(std::declval<From>())),
                std::true_type{});
template <class, class>
auto test_implicitly_convertible(...) -> std::false_type;

} // namespace detail

template <class From, class To>
struct is_convertible
    : std::integral_constant<
          bool, (decltype(detail::test_returnable<To>(0))::value&& decltype(
                    detail::test_implicitly_convertible<From, To>(0))::value) ||
                    (std::is_void<From>::value && std::is_void<To>::value)> {};

template <class From, class To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

} // namespace std
