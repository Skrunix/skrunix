#pragma once

#include <integers>

template <typename Type>
inline Type* Align(void* pointer, USize alignment) {
	UIntPtr value = reinterpret_cast<uintptr_t>(pointer);
	--alignment;
	value = (value + alignment) & (~alignment);
	return reinterpret_cast<Type*>(value.value);
}
