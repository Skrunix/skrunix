#pragma once

namespace std {

template <class T>
struct remove_cv {
	typedef T type;
};

template <class T>
struct remove_cv<const T> {
	typedef T type;
};

template <class T>
struct remove_cv<volatile T> {
	typedef T type;
};

template <class T>
struct remove_cv<const volatile T> {
	typedef T type;
};

template <class T>
using remove_cv_t = typename remove_cv<T>::type;

} // namespace std
