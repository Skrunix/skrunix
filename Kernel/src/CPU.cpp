#include "CPU.hpp"

UIntPtr CPU::GetCR3() {
	UIntPtr cr3;
	asm volatile("movq %%cr3, %%rax" : "=a"(cr3.value));
	return cr3;
}

void CPU::SetCR3(UIntPtr value) {
	asm volatile("movq %%rax, %%cr3" : : "a"(value) : "memory");
}
