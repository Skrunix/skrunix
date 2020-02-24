#include "GDT/GDT.hpp"
#include "IDT/IDT.hpp"
#include "IO.hpp"
#include "Memory/BuddyAlloc.hpp"
#include "PIC.hpp"
#include "PIT.hpp"
#include "Screen.hpp"
#include "Serial.hpp"

#include <ValueOf.hpp>

extern "C" {
[[noreturn]] void main();
}

extern UInt64 KernelTextSize;
extern UInt64 KernelDataSize;
extern UInt64 KernelBSSSize;
void*         KernelTextSize2 = &KernelTextSize;
void*         KernelDataSize2 = &KernelDataSize;
void*         KernelBSSSize2  = &KernelBSSSize;

extern UInt64 KernelEnd; // Defined in linker script
void*         allocAddress = &KernelEnd;

UInt8   screenData[sizeof(Screen)];
Screen* screen;
PIT*    globalPIT;

void main() {
	screen =
	    reinterpret_cast<Screen*>(reinterpret_cast<uintptr_t>(&screenData));
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
			screen->SetForeground(static_cast<Screen::Color>(fg));
			screen->setBackground(static_cast<Screen::Color>(bg));
			screen->WriteRaw('E');
		}
	}

	screen->SetForeground(Screen::Color::LightGray);
	screen->setBackground(Screen::Color::Black);
	screen->Write("\r\n\n");
	screen->WriteHex(UIntPtr(reinterpret_cast<uintptr_t>(screen)));
	screen->Write("\r\n");
	screen->WriteHex(UIntPtr(reinterpret_cast<uintptr_t>(allocAddress)));

	screen->Write("\r\n\n");

	GDT gdt;
	IDT idt;
	PIC pic;
	PIT pit(0x20);

	globalPIT = &pit;

	Serial serial;
	serial.Write("HELLO\r\n");
	serial.Write("Text size: ");
	serial.WriteHex(reinterpret_cast<uint64_t>(KernelTextSize2));
	serial.Write("\r\n");
	serial.Write("Data size: ");
	serial.WriteHex(reinterpret_cast<uint64_t>(KernelDataSize2));
	serial.Write("\r\n");
	serial.Write("BSS  size: ");
	serial.WriteHex(reinterpret_cast<uint64_t>(KernelBSSSize2));
	serial.Write("\r\n");

	UInt*         rangesCount = reinterpret_cast<UInt*>(0x9000);
	AddressRange* ranges      = reinterpret_cast<AddressRange*>(0x9018);
	BuddyAlloc    pageAllocator(ranges, *rangesCount);

	serial.Write("RAM Pages: ");
	serial.WriteHex(pageAllocator.pageCount);
	serial.Write("\r\n");

	UInt rangeCount = *rangesCount;
	for (UInt i = 0; i < rangeCount; ++i) {
		AddressRange range = ranges[i.value];
		screen->WriteHex(UIntPtr(range.base.value));
		screen->Write(" ");
		screen->WriteHex(UIntPtr(range.length.value));
		screen->Write(" ");
		if (range.type == AddressRange::Type::Usable) {
			screen->Write("Usable");
		} else if (range.type == AddressRange::Type::Reserved) {
			screen->Write("Reserved");
		} else if (range.type == AddressRange::Type::ACPI_Reclaimable) {
			screen->Write("ACPI reclaimable");
		} else if (range.type == AddressRange::Type::ACPI_NVS) {
			screen->Write("ACPI NVS");
		} else if (range.type == AddressRange::Type::Bad) {
			screen->Write("Bad");
		} else {
			screen->Write("? ");
			screen->WriteHex(UIntPtr(ValueOf(range.type)));
		}
		screen->Write("\r\n");
	}
	screen->Write("RAM Pages: ");
	screen->WriteHex(UIntPtr(pageAllocator.pageCount.value));
	screen->Write("\r\n");
	screen->Write("\r\n");

	asm volatile("int $0x0");
	asm volatile("int $0xff");
	asm volatile("sti");

	while (1)
		;
}

extern "C" {
typedef struct {
	UInt64 interruptNumber;
} IRQRegisters;

UInt64 timerCount = 0;

void timerHandler(IRQRegisters) {
	screen->Write("\r");
	screen->WriteHex(UIntPtr((++timerCount).value));
	PIC::EOI1();
}

#define KB_DATA 0x60
#define KB_STATUS 0x64

char qwerty[256] = {
    '\0', '\0', '1',  '2',  '3',  '4',  '5',  '6',
    '7',  '8',  '9',  '0',  '-',  '=',  '\0', '\0',

    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
    'o',  'p',  '[',  ']',  '\0', '\0', 'a',  's',

    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',
    '\'', '`',  '\0', '\\', 'z',  'x',  'c',  'v',

    'b',  'n',  'm',  ',',  '.',  '/',  '\0', '\0',
    '\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0',
};
char QWERTY[256] = {
    '\0', '\0', '!',  '@',  '#',  '$',  '%',  '^',
    '&',  '*',  '(',  ')',  '_',  '+',  '\0', '\0',

    'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',
    'O',  'P',  '{',  '}',  '\0', '\0', 'A',  'S',

    'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',
    '"',  '~',  '\0', '|',  'Z',  'X',  'C',  'V',

    'B',  'N',  'M',  '<',  '>',  '?',  '\0', '\0',
    '\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0',
};
bool shift = false;

UInt16 NOTES[10] = {261, 294, 330, 349, 392, 440, 493, 523, 587, 659};

void keyboardHandler(IRQRegisters) {
	auto status = IO::in(KB_STATUS);
	if ((status & 0x01) != 0) {
		UInt8 keycode = IO::in(KB_DATA);
		if ((keycode & 0x80) == 0) {
			char character = '\0';
			if (shift) {
				character = QWERTY[keycode.value];
			} else {
				character = qwerty[keycode.value];
			}
			if (character != '\0') {
				screen->Write(character);
			} else if (keycode == 0x2A) { // LShift
				shift = true;
			} else if (keycode == 0x1C) { // Enter
				screen->Write("\r\n");
			} else if (keycode == 0x0E) { // Backspace
				screen->Write(8);
			} else {
				screen->WriteHex(keycode);
			}
			if (character >= '0' && character <= '9') {
				UInt16 frequency = NOTES[character - '0'];
				globalPIT->Beep(frequency);
			}
		} else {
			if (keycode == 0xAA) { // LShift
				shift = false;
			}
			globalPIT->Stop();
		}
	}
	PIC::EOI1();
}

void isrHandler(IRQRegisters registers) {
	if (registers.interruptNumber == 0x20) {
		return timerHandler(registers);
	}
	if (registers.interruptNumber == 0x21) {
		return keyboardHandler(registers);
	}

	screen->Write("Got interrupt: ");
	screen->WriteHex(UIntPtr(registers.interruptNumber.value));
	screen->Write("\r\n");
}
}
