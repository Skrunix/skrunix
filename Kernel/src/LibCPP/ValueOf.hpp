#pragma once

#include <type_traits.hpp>

template <typename Enum>
[[nodiscard]] auto ValueOf(const Enum value) {
	return static_cast<std::underlying_type_t<Enum>>(value);
}
