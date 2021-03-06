#pragma once

#include "Attributes.hpp"

#include <Integers/Integers.hpp>

struct CPU {
	ALWAY_INLINE static UIntPtr GetCR3() {
		uintptr_t cr3;
		asm volatile("movq %%cr3, %%rax" : "=a"(cr3));
		return cr3;
	}

	ALWAY_INLINE static void SetCR3(UIntPtr value) {
		asm volatile("movq %%rax, %%cr3" : : "a"(value) : "memory");
	}
};
