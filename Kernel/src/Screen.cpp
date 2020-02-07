#include "Screen.hpp"

uint8_t* const BasePointer = (uint8_t*)0xB8000;

Screen::Screen()
    : x(0)
    , y(0)
    , maxX(80)
    , foreground(Color::LightGray)
    , background(Color::Black) {}
Screen::~Screen() {}

void Screen::Write(char character) {
	if (character == '\r') {
		this->x = 0;
		return;
	}
	if (character == '\n') {
		++this->y;
		return;
	}
	this->WriteRaw(character);
}

void Screen::Write(const char* string) {
	char character;
	while ((character = *(string++))) {
		this->Write(character);
	}
}

void Screen::WriteRaw(char character) {
	if (this->x >= this->maxX) {
		this->x = 0;
		++this->y;
	}

	auto offset = this->y * this->maxX + this->x;
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
