#pragma once

namespace std {

template <class T>
struct remove_const {
	typedef T type;
};

template <class T>
struct remove_const<const T> {
	typedef T type;
};

template <class T>
using remove_const_t = typename remove_const<T>::type;

} // namespace std
