#pragma once

#include <Integers/Integers.hpp>
#include <type_traits>

template <typename Enum>
[[nodiscard]] std::enable_if_t<
    std::is_enum_v<Enum> &&
        std::is_same_v<UInt8::BackingType, std::underlying_type_t<Enum>>,
    UInt8>
ValueOf(const Enum& value) {
	return static_cast<std::underlying_type_t<Enum>>(value);
}

template <typename Enum>
[[nodiscard]] std::enable_if_t<
    std::is_enum_v<Enum> &&
        std::is_same_v<UInt32::BackingType, std::underlying_type_t<Enum>>,
    UInt32>
ValueOf(const Enum& value) {
	return static_cast<std::underlying_type_t<Enum>>(value);
}
