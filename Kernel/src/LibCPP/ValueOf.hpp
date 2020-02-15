#pragma once

#include <type_traits.hpp>

template <typename Enum>
typename std::underlying_type<Enum>::type ValueOf(Enum const value) {
	return static_cast<typename std::underlying_type<Enum>::type>(value);
}
