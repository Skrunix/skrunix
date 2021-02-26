#pragma once

#include <type_trait/is_same.hpp>
#include <type_trait/remove_cv.hpp>

namespace std {

template <class T>
struct is_void : std::is_same<void, typename std::remove_cv<T>::type> {};

template <class T>
inline constexpr bool is_void_v = is_void<T>::value;

} // namespace std
