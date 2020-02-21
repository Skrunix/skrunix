#include "Serial.hpp"
#include "IO.hpp"

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

Serial::Serial() {
	IO::out(COM1 + 1, 0x00); // Disable all interrupts
	IO::out(COM1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
	IO::out(COM1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
	IO::out(COM1 + 1, 0x00); //                  (hi byte)
	IO::out(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
	IO::out(COM1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
	IO::out(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

Serial::~Serial() {}

void Serial::Write(char character) {
	while (!this->CanWrite())
		;
	IO::out(COM1, character);
}

void Serial::Write(const char* string) {
	char character;
	while ((character = *(string++))) {
		this->Write(character);
	}
}

bool Serial::CanWrite() { return IO::in(COM1 + 5) & 0x20; }