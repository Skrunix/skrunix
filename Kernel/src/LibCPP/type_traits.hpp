#pragma once

namespace std {

template <class Type>
struct is_enum {
	constexpr static bool value = __is_enum(Type);
};

template <class Type>
struct underlying_type {
	typedef __underlying_type(Type) type;
};

} // namespace std

namespace std {

template <class T>
using underlying_type_t = typename underlying_type<T>::type;

} // namespace std
