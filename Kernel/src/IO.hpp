#pragma once

#include <Integers/Integers.hpp>

class IO {
  public:
	[[gnu::always_inline]] inline static UInt8 in(UInt16 port) {
		UInt8 ret = 0;
		asm volatile("inb %1, %0" : "=a"(ret.value) : "Nd"(port));
		return ret;
	}

	[[gnu::always_inline]] inline static void out(UInt16 port, UInt8 value) {
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	}
};
