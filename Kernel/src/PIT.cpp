#include "PIT.hpp"
#include "IO.hpp"

PIT::PIT(uint16_t frequency) {
	uint16_t divisor = 1193180 / frequency;

	IO::out(0x43, 0x36);
	IO::out(0x40, divisor & 0xFF);
	IO::out(0x40, (divisor >> 8) & 0xFF);
}

PIT::~PIT() {}
