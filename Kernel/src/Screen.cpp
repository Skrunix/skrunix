#include "Screen.hpp"

uint8_t* const BasePointer = (uint8_t*)0xB8000;

Screen::Screen()
    : x(0)
    , foreground(Color::LightGray)
    , background(Color::Black) {}
Screen::~Screen() {}

void Screen::WriteRaw(char character) {
	auto offset = this->x;
	auto memory = BasePointer + 2 * offset;

	*(memory + 0) = character;
	*(memory + 1) = (this->background << 4) | this->foreground;

	++this->x;
}

void Screen::WriteRaw(const char* string) {
	char character;
	while ((character = *(string++))) {
		this->WriteRaw(character);
	}
}

void Screen::SetForeground(Color color) { this->foreground = color; }
void Screen::setBackground(Color color) { this->background = color; }
