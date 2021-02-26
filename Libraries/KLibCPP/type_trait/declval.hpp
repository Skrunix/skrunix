#pragma once

#include <type_trait/add_rvalue_reference.hpp>

namespace std {

template <class T>
typename std::add_rvalue_reference<T>::type declval() noexcept {
	return __declval<T>(0);
}

} // namespace std
