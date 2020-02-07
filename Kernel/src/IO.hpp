#pragma once

#include "types.h"

class IO {
  public:
	static inline void out(uint16_t port, uint8_t value) {
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	}
};
