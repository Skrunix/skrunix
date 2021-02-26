#pragma once

#include <type_trait/type_identity.hpp>

namespace std {

namespace detail {

template <class T>
auto try_add_rvalue_reference(int) -> std::type_identity<T&&>;
template <class T>
auto try_add_rvalue_reference(...) -> std::type_identity<T>;

} // namespace detail

template <class T>
struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {
};

template <class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

} // namespace std
