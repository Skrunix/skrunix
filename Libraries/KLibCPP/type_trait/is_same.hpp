#pragma once

#include <type_trait/bool_constant.hpp>

namespace std {

template <class T, class U>
struct is_same : std::false_type {};

template <class T>
struct is_same<T, T> : std::true_type {};

template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;

} // namespace std
