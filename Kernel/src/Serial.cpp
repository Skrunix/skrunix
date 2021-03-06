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

void Serial::WriteHex(UInt32 value) {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (UInt8 i = (sizeof(UInt32) * 8 - 4); i > 0; i -= 4) {
		UInt8 halfByte =
		    (static_cast<uint32_t>(value) >> static_cast<uint8_t>(i)) & 0xF;
		this->Write(lookup[static_cast<uint8_t>(halfByte)]);
	}
	this->Write(lookup[static_cast<uint32_t>(value) & 0xF]);
}

void Serial::WriteHex(UInt64 value) {
	this->WriteHex(UIntPtr(static_cast<uint64_t>(value)));
}

void Serial::WriteHex(UIntPtr value) {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (UInt8 i = (sizeof(UIntPtr) * 8 - 4); i > 0; i -= 4) {
		UInt8 halfByte =
		    (static_cast<uintptr_t>(value) >> static_cast<uint8_t>(i)) & 0xF;
		this->Write(lookup[static_cast<uint8_t>(halfByte)]);
	}
	this->Write(lookup[static_cast<uintptr_t>(value) & 0xF]);
}

void Serial::WriteFormat(const char* string, UIntPtr value) {
	char character;
	while ((character = *(string++))) {
		if (character == '%') {
			this->WriteHex(value);
		} else {
			this->Write(character);
		}
	}
}

Bool Serial::CanWrite() { return (IO::in(COM1 + 5) & 0x20) != 0; }
