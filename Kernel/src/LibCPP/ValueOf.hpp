#pragma once

#include <type_traits>

template <typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
[[nodiscard]] auto ValueOf(const Enum& value) {
	return static_cast<std::underlying_type_t<Enum>>(value);
}
