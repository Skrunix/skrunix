#pragma once

#include <Integers.hpp>

template <typename Type>
[[gnu::always_inline]] inline Type* Align(void* pointer, USize alignment) {
	UIntPtr value = reinterpret_cast<uintptr_t>(pointer);
	--alignment;
	value = (value + UIntPtr(UInt64(alignment))) & UIntPtr(UInt64(~alignment));
	return reinterpret_cast<Type*>(value.value);
}
