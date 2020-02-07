#include "Screen.hpp"

uint8_t* const BasePointer = (uint8_t*)0xB8000;

Screen::Screen() : x(0) {}
Screen::~Screen() {}

void Screen::WriteRaw(char character) {
	auto offset = this->x;
	auto memory = BasePointer + 2 * offset;

	*memory = character;
	*(memory + 1) = 0x53;

	++this->x;
}

void Screen::WriteRaw(const char* string) {
	char character;
	while ((character = *(string++))) {
		this->WriteRaw(character);
	}
}
