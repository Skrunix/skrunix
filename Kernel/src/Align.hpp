#pragma once

#include <Integers/Integers.hpp>

template <typename T, uintmax_t Alignment = 4096>
[[gnu::always_inline]] inline T* Align(const void* const pointer) {
	constexpr UIntPtr mask = Alignment - 1;

	auto value = UIntPtr::From(pointer);
	value      = (value + mask) & ~mask;
	return value.To<T*>();
}

// Align to upper boundary if not already aligned
template <uintmax_t Alignment = 4096>
[[gnu::always_inline]] inline constexpr UIntPtr Align(UIntPtr pointer) {
	constexpr UIntPtr mask = Alignment - 1;
	return (pointer + mask) & ~mask;
}
static_assert(Align<0x100>(UIntPtr(0x100)) == 0x100);
static_assert(Align<0x100>(UIntPtr(0x101)) == 0x200);

// Align to lower boundary if not already aligned
template <uintmax_t Alignment = 4096>
[[gnu::always_inline]] inline constexpr UIntPtr AlignDown(UIntPtr pointer) {
	constexpr UIntPtr mask = Alignment - 1;
	return pointer & ~mask;
}
static_assert(AlignDown<0x100>(UIntPtr(0x100)) == 0x100);
static_assert(AlignDown<0x100>(UIntPtr(0x101)) == 0x100);

// Align to upper boundary
template <uintmax_t Alignment = 4096>
[[gnu::always_inline]] inline constexpr UIntPtr AlignUp(UIntPtr pointer) {
	auto aligned = Align<Alignment>(pointer);
	if (aligned == pointer) {
		return aligned + Alignment;
	}
	return aligned;
}
static_assert(AlignUp<0x100>(UIntPtr(0x100)) == 0x200);
static_assert(AlignUp<0x100>(UIntPtr(0x101)) == 0x200);
