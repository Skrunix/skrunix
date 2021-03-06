#pragma once

#include "Attributes.hpp"

#include <Integers/Integers.hpp>

class IO {
  public:
	ALWAY_INLINE static UInt8 in(UInt16 port) {
		uint8_t ret = 0;
		asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
		return ret;
	}

	ALWAY_INLINE static void out(UInt16 port, UInt8 value) {
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	}
};
