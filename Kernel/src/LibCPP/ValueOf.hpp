#pragma once

#include <type_traits>

template <typename Enum>
[[nodiscard]] std::enable_if_t<std::is_enum_v<Enum>,
                               std::underlying_type_t<Enum>>
ValueOf(const Enum& value) {
	return static_cast<std::underlying_type_t<Enum>>(value);
}
