#pragma once

namespace std {

template <class T>
struct remove_reference {
	typedef T type;
};

template <class T>
struct remove_reference<T&> {
	typedef T type;
};

template <class T>
struct remove_reference<T&&> {
	typedef T type;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

} // namespace std
