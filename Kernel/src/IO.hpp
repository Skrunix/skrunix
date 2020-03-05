#pragma once

#include <Inline.hpp>
#include <integers>

class IO {
  public:
	static FORCE_INLINE UInt8 in(UInt16 port) {
		UInt8 ret = 0;
		asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
		return ret;
	}

	static FORCE_INLINE void out(UInt16 port, UInt8 value) {
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	}
};
