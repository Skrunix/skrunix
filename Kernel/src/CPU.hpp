#pragma once

#include <Integers/Integers.hpp>

struct CPU {
	[[gnu::always_inline]] inline static UIntPtr GetCR3() {
		uintptr_t cr3;
		asm volatile("movq %%cr3, %%rax" : "=a"(cr3));
		return cr3;
	}

	[[gnu::always_inline]] inline static void SetCR3(UIntPtr value) {
		asm volatile("movq %%rax, %%cr3" : : "a"(value) : "memory");
	}
};
