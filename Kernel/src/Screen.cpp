#include "Screen.hpp"

uint8_t* const BasePointer = (uint8_t*)0xB8000;

Screen::Screen()
    : x(0)
    , y(0)
    , maxX(80)
    , maxY(25)
    , foreground(Color::LightGray)
    , background(Color::Black) {}
Screen::~Screen() {}

void Screen::Clear() {
	this->SetForeground(Color::LightGray);
	this->setBackground(Color::Black);

	auto memory = (uint16_t*)BasePointer;
	auto offset = this->maxX * this->maxY;

	uint16_t data = (this->background << 12) | (this->foreground << 8) | ' ';
	for (uint16_t i = 0; i < offset; ++i) {
		*(memory++) = data;
	}
}

void Screen::ScrollUp() {
	auto toMem   = (uint16_t*)BasePointer;
	auto fromMem = (uint16_t*)BasePointer + this->maxX;
	auto offset  = this->maxX * (this->maxY - 1);

	for (uint16_t i = 0; i < offset; ++i) {
		*(toMem++) = *(fromMem++);
	}

	uint16_t data = (this->background << 12) | (this->foreground << 8) | ' ';
	for (uint16_t i = 0; i < this->maxX; ++i) {
		*(toMem++) = data;
	}

	if (this->y > 0) {
		--this->y;
	}
}

void Screen::Write(char character) {
	if (character == '\r') {
		this->x = 0;
		return;
	}
	if (character == '\n') {
		this->IncrementY();
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
		this->IncrementY();
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

void Screen::IncrementY() {
	if (this->y >= this->maxY) {
		this->ScrollUp();
	} else {
		++this->y;
	}
}
