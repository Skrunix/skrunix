#include "IDT.hpp"
#include "IO.hpp"
#include "PIC.hpp"
#include "Screen.hpp"

uint8_t screenData[sizeof(Screen)];
Screen* screen;

void main() {
	screen  = (Screen*)&screenData;
	*screen = Screen();
	screen->Clear();

	screen->SetForeground(Screen::Color::Red);
	screen->setBackground(Screen::Color::Black);
	screen->Write("\nSkrunix\r\n\n");
	screen->ScrollUp();

	screen->SetForeground(Screen::Color::Blue);
	screen->setBackground(Screen::Color::Red);
	screen->WriteRaw("Character test:");

	screen->SetForeground(Screen::Color::Magenta);
	screen->setBackground(Screen::Color::Cyan);
	screen->WriteRaw('\0');
	for (char i = 1; i != 0; ++i) {
		screen->WriteRaw(i);
	}

	screen->Write("\r\n\n");
	screen->SetForeground(Screen::Color::Blue);
	screen->setBackground(Screen::Color::LightRed);
	screen->WriteRaw("Color test:");
	for (char fg = 0; fg < 0x10; ++fg) {
		for (char bg = 0; bg < 0x10; ++bg) {
			screen->SetForeground((Screen::Color)fg);
			screen->setBackground((Screen::Color)bg);
			screen->WriteRaw('E');
		}
	}

	screen->SetForeground(Screen::Color::LightGray);
	screen->setBackground(Screen::Color::Black);
	screen->Write("\r\n\n");
	screen->WriteHex((uintptr_t)screen);

	screen->Write("\r\n\n");

	IDT idt;
	PIC pic;

	asm volatile("int $0x3");
	asm volatile("int $0x4");
	asm volatile("sti");

	while (1)
		;
}

extern "C" {
void kmainpp() { main(); }
}

extern "C" {
typedef struct {
	uint64_t interruptNumber;
} IRQRegisters;

#define KB_DATA 0x60
#define KB_STATUS 0x64

void isrHandler(IRQRegisters registers) {
	screen->Write("Got interrupt: ");
	screen->WriteHex(registers.interruptNumber);

	// PS2 Keyboard Interrupt
	if (registers.interruptNumber == 0x21) {
		screen->Write(" - ");
		auto status = IO::in(KB_STATUS);
		if (status & 0x01) {
			uint8_t keycode = IO::in(KB_DATA);
			if ((keycode & 0x80) == 0) {
				screen->WriteHex(keycode);
			} else {
				screen->Write("-");
				screen->WriteHex((uint8_t)(keycode & 0x7F));
			}
		}
		PIC::EOI1();
	}

	screen->Write("\r\n");
}
}
