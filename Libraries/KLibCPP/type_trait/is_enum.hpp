#pragma once

namespace std {

template <class T>
struct is_enum {
	constexpr static bool value = __is_enum(T);
};

template <class T>
inline constexpr bool is_enum_v = is_enum<T>::value;

} // namespace std
