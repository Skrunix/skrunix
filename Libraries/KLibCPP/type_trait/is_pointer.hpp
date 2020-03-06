#pragma once

#include <type_trait/bool_constant.hpp>
#include <type_trait/remove_cv.hpp>

namespace std {

template <class T>
struct is_pointer_helper : false_type {};

template <class T>
struct is_pointer_helper<T*> : true_type {};

template <class T>
struct is_pointer : is_pointer_helper<remove_cv_t<T>> {};

template <class T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;

} // namespace std
