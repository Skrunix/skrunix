#pragma once

#include <Integers/Integers.hpp>
#include <type_traits>

template <typename T>
concept EnumType = std::is_enum_v<T>;

template <EnumType T>
[[nodiscard]] std::underlying_type_t<T> ValueOf(const T& value) {
	return static_cast<std::underlying_type_t<T>>(value);
}
