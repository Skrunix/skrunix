#include "Screen.hpp"
#include "IO.hpp"

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

	this->MoveCursor(0, 0);
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
		this->MoveCursor(this->x, this->y - 1);
	}
}

void Screen::Write(char character) {
	if (character == '\r') {
		this->x = 0;
		this->MoveCursor(0, this->y);
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

void Screen::WriteHex(uint8_t value) {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	this->Write(lookup[(value >> 4) & 0xF]);
	this->Write(lookup[value & 0xF]);
}

void Screen::WriteHex(uintptr_t value) {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (uint8_t i = 60; i > 0; i -= 4) {
		uint8_t halfByte = (value >> i) & 0xF;
		this->Write(lookup[halfByte]);
	}
	this->Write(lookup[value & 0xF]);
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

	this->MoveCursor(this->x + 1, this->y);
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
	++this->y;
	if (this->y >= this->maxY) {
		this->ScrollUp();
	}
	this->MoveCursor(this->x, this->y);
}

void Screen::MoveCursor(uint16_t x, uint16_t y) {
	this->x = x;
	this->y = y;
	this->UpdateCursor();
}

void Screen::UpdateCursor() {
	auto offset = this->y * this->maxX + this->x;

	// Write cursor position
	IO::out(0x3D4, 14);
	IO::out(0x3D5, offset >> 8);
	IO::out(0x3D4, 15);
	IO::out(0x3D5, offset);
}
