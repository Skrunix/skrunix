#include "Debug.hpp"

Debug::Debug(void (*writeFunction)(char))
    : write(writeFunction) {}
Debug ::~Debug() {}

void Debug::Write(char character) const { this->write(character); }

void Debug::Write(const char* string) const {
	char character;
	while ((character = *(string++))) {
		this->Write(character);
	}
}

void Debug::WriteHex(UInt32 value) const {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (UInt8 i = (UInt32::BitWidth - 4); i > 0; i -= 4) {
		UInt8 halfByte = (value.value >> i.value) & 0xF;
		this->Write(lookup[halfByte.value]);
	}
	this->Write(lookup[value.value & 0xF]);
}

void Debug::WriteHex(UIntPtr value) const {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (UInt8 i = (UIntPtr::BitWidth - 4); i > 0; i -= 4) {
		UInt8 halfByte = (value.value >> i.value) & 0xF;
		this->Write(lookup[halfByte.value]);
	}
	this->Write(lookup[value.value & 0xF]);
}

void Debug::WriteHex(USize value) const {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (UInt8 i = (USize::BitWidth - 4); i > 0; i -= 4) {
		UInt8 halfByte = (value.value >> i.value) & 0xF;
		this->Write(lookup[halfByte.value]);
	}
	this->Write(lookup[value.value & 0xF]);
}
