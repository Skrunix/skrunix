#pragma once

#include <Integers/Integers.hpp>

template <typename T, int Alignment = 4096>
[[gnu::always_inline]] inline T* Align(const void* const pointer) {
	constexpr UIntPtr mask = Alignment - 1;

	auto value = UIntPtr::From(pointer);
	value      = (value + mask) & ~mask;
	return value.To<T*>();
}

template <int Alignment = 4096>
[[gnu::always_inline]] inline UIntPtr Align(UIntPtr pointer) {
	constexpr UIntPtr mask = Alignment - 1;
	return (pointer + mask) & ~mask;
}
