#pragma once

#include <Integers.hpp>

template <typename T>
[[gnu::always_inline]] inline T* Align(const void* const pointer,
                                       const USize       alignment) {
	auto value = UIntPtr::From(pointer);
	auto mask  = alignment - 1;
	value      = (value + UIntPtr(mask)) & UIntPtr(~mask);
	return value.To<T*>();
}
