#pragma once

#include <integers>
#include <Inline.hpp>

template <typename Type>
FORCE_INLINE Type* Align(void* pointer, USize alignment) {
	UIntPtr value = reinterpret_cast<uintptr_t>(pointer);
	--alignment;
	value = (value + alignment) & (~alignment);
	return reinterpret_cast<Type*>(value.value);
}
