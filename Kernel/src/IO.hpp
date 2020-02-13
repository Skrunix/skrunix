#pragma once

#include "types.h"

class IO {
  public:
	static inline uint8_t in(uint16_t port) {
		uint8_t ret;
		asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
		return ret;
	}

	static inline void out(uint16_t port, uint8_t value) {
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	}
};
