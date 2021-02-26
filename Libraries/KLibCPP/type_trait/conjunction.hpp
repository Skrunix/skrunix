#pragma once

#include <type_trait/bool_constant.hpp>
#include <type_trait/conditional.hpp>

namespace std {

template <class...>
struct conjunction : std::true_type {};

template <class B1>
struct conjunction<B1> : B1 {};

template <class B1, class... Bn>
struct conjunction<B1, Bn...>
    : std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

template <class... B>
inline constexpr bool conjunction_v = conjunction<B...>::value;

} // namespace std
