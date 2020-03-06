#pragma once

namespace std {

template <class T>
struct underlying_type {
	typedef __underlying_type(T) type;
};

template <class T>
using underlying_type_t = typename underlying_type<T>::type;

} // namespace std
