#pragma once

namespace std {

template <class T>
struct remove_volatile {
	typedef T type;
};

template <class T>
struct remove_volatile<volatile T> {
	typedef T type;
};

template <class T>
using remove_volatile_t = typename remove_volatile<T>::type;

} // namespace std
