#pragma once

#include <integers>

class IO {
  public:
	static inline UInt8 in(UInt16 port) {
		UInt8 ret = 0;
		asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
		return ret;
	}

	static inline void out(UInt16 port, UInt8 value) {
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	}
};
