#pragma once

namespace std {

template <class T>
struct type_identity {
	using type = T;
};

template <class T>
using type_identity_t = typename type_identity<T>::type;

} // namespace std
