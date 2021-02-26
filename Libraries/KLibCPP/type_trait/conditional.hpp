#pragma once

namespace std {

template <bool B, class T, class F>
struct conditional {
	typedef T type;
};

template <class T, class F>
struct conditional<false, T, F> {
	typedef F type;
};

template <bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

} // namespace std
