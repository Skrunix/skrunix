#include "Screen.hpp"

#include "IO.hpp"

#include <ValueOf.hpp>

UInt8* const BasePointer = reinterpret_cast<UInt8*>(0xB8000);

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

	auto memory = reinterpret_cast<UInt16*>(BasePointer);
	auto offset = this->maxX * this->maxY;

	UInt16 data = (ValueOf(this->background) << 12) |
	              (ValueOf(this->foreground) << 8) | ' ';
	for (UInt16 i = 0; i < offset; ++i) {
		*(memory++) = data;
	}

	this->MoveCursor(0, 0);
}

void Screen::ScrollUp() {
	auto toMem   = reinterpret_cast<UInt16*>(BasePointer);
	auto fromMem = reinterpret_cast<UInt16*>(BasePointer) + this->maxX.value;
	auto offset  = this->maxX * (this->maxY - 1);

	for (UInt16 i = 0; i < offset; ++i) {
		*(toMem++) = *(fromMem++);
	}

	UInt16 data = (ValueOf(this->background) << 12) |
	              (ValueOf(this->foreground) << 8) | ' ';
	for (UInt16 i = 0; i < this->maxX; ++i) {
		*(toMem++) = data;
	}

	if (this->y > 0) {
		this->MoveCursor(this->x, this->y - 1);
	}
}

void Screen::Write(char character) {
	if (character == '\r') {
		this->MoveCursor(0, this->y);
		return;
	}
	if (character == '\n') {
		this->IncrementY();
		return;
	}
	if (character == 8) { // Backspace
		if (this->x > 0) {
			--this->x;
		}
		this->WriteRaw(' ');
		this->MoveCursor(this->x - 1, this->y);
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

void Screen::WriteHex(UInt8 value) {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	this->Write(lookup[value.high().value]);
	this->Write(lookup[value.low().value]);
}

void Screen::WriteHex(UIntPtr value) {
	static char lookup[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	this->Write("0x");
	for (UInt8 i = 60; i > 0; i -= 4) {
		UInt8 halfByte = (value.value >> i.value) & 0xF;
		this->Write(lookup[halfByte.value]);
	}
	this->Write(lookup[value.value & 0xF]);
}

void Screen::WriteRaw(char character) {
	if (this->x >= this->maxX) {
		this->x = 0;
		this->IncrementY();
	}

	auto offset = this->y * this->maxX + this->x;
	auto memory = BasePointer + 2 * offset.value;

	*(memory + 0) = character;
	*(memory + 1) =
	    (ValueOf(this->background) << 4) | ValueOf(this->foreground);

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

void Screen::MoveCursor(UInt16 newX, UInt16 newY) {
	this->x = newX;
	this->y = newY;
	this->UpdateCursor();
}

void Screen::UpdateCursor() {
	auto offset = this->y * this->maxX + this->x;

	// Write cursor position
	IO::out(0x3D4, 14);
	IO::out(0x3D5, offset.high().value);
	IO::out(0x3D4, 15);
	IO::out(0x3D5, offset.low().value);
}
