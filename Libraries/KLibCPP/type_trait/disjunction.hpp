#pragma once

#include <type_trait/bool_constant.hpp>
#include <type_trait/conditional.hpp>

namespace std {

template <class...>
struct disjunction : std::false_type {};

template <class B1>
struct disjunction<B1> : B1 {};

template <class B1, class... Bn>
struct disjunction<B1, Bn...>
    : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};

template <class... B>
inline constexpr bool disjunction_v = disjunction<B...>::value;

} // namespace std
