#include "Align.hpp"
#include "CPU.hpp"
#include "Debug.hpp"
#include "GDT/GDT.hpp"
#include "IDT/IDT.hpp"
#include "IO.hpp"
#include "Memory/PageTable.hpp"
#include "Memory/PhysAlloc.hpp"
#include "Memory/PhysMap.hpp"
#include "Memory/VirtAlloc.hpp"
#include "PIC.hpp"
#include "PIT.hpp"
#include "Screen.hpp"
#include "Serial.hpp"
#include "ValueOf.hpp"

extern "C" {
[[noreturn]] void main();
}

extern USize KernelTextSize;
extern USize KernelDataSize;
extern USize KernelBSSSize;
void*        KernelTextSize2 = &KernelTextSize;
void*        KernelDataSize2 = &KernelDataSize;
void*        KernelBSSSize2  = &KernelBSSSize;

extern UInt64 KernelStart; // Defined in linker script
extern UInt64 KernelEnd;   // Defined in linker script
void*         kernelStartAddress = &KernelStart;
void*         kernelEndAddress   = &KernelEnd;

Serial* globalSerial;
Screen* globalScreen;
PIT*    globalPIT;

void nullWrite(char) {}
void serialWrite(char character) { globalSerial->Write(character); }
void screenWrite(char character) { globalScreen->Write(character); }

void main() {
	UIntPtr kernelOffset = 0xFFFF800000000000;

	Serial serial;
	globalSerial = &serial;
	Screen screen(reinterpret_cast<UInt8*>(0xB8000));
	globalScreen = &screen;

	Debug nullDebug(nullWrite);
	Debug serialDebug(serialWrite);
	Debug screenDebug(screenWrite);

	PageTable::PageTableEntryTest(serialDebug);

	serial.Write("Skrunix\r\n");
	serial.Write("Text size: ");
	serial.WriteHex(UIntPtr::From(KernelTextSize2));
	serial.Write("\r\n");
	serial.Write("Data size: ");
	serial.WriteHex(UIntPtr::From(KernelDataSize2));
	serial.Write("\r\n");
	serial.Write("BSS  size: ");
	serial.WriteHex(UIntPtr::From(KernelBSSSize2));
	serial.Write("\r\n");

	screen.Clear();

	screen.SetForeground(Screen::Color::Red);
	screen.setBackground(Screen::Color::Black);
	screen.Write("\nSkrunix\r\n\n");
	screen.ScrollUp();

	screen.SetForeground(Screen::Color::Blue);
	screen.setBackground(Screen::Color::Red);
	screen.WriteRaw("Character test:");

	screen.SetForeground(Screen::Color::Magenta);
	screen.setBackground(Screen::Color::Cyan);
	screen.WriteRaw('\0');
	for (char i = 1; i != 0; ++i) {
		screen.WriteRaw(i);
	}

	screen.Write("\r\n\n");
	screen.SetForeground(Screen::Color::Blue);
	screen.setBackground(Screen::Color::LightRed);
	screen.WriteRaw("Color test:");
	for (char fg = 0; fg < 0x10; ++fg) {
		for (char bg = 0; bg < 0x10; ++bg) {
			screen.SetForeground(static_cast<Screen::Color>(fg));
			screen.setBackground(static_cast<Screen::Color>(bg));
			screen.WriteRaw('E');
		}
	}
	screen.Write("\r\n\n");

	screen.SetForeground(Screen::Color::LightGray);
	screen.setBackground(Screen::Color::Black);

	USize*        rangesCount = reinterpret_cast<USize*>(0x9000);
	AddressRange* ranges      = reinterpret_cast<AddressRange*>(0x9018);

	PhysAlloc pageAllocator(
	    ranges, *rangesCount, UIntPtr::From(kernelStartAddress),
	    UIntPtr::From(kernelEndAddress), kernelOffset, serialDebug);

	// Reserve Page Table
	pageAllocator.reserve(0xA000, 1);
	pageAllocator.reserve(0xB000, 1);
	pageAllocator.reserve(0xC000, 1);
	pageAllocator.reserve(0xD000, 1);
	pageAllocator.reserve(0xE000, 1);
	pageAllocator.reserve(0xF000, 1);
	// Reserve Screen
	pageAllocator.reserve(0xB8000, 1);

	GDT gdt;
	IDT idt(kernelOffset + pageAllocator.reserve(0, 1));
	PIC pic;
	PIT pit(0x20);

	globalPIT = &pit;

	serialDebug.Write("RAM Pages: ");
	serialDebug.WriteHex(pageAllocator.totalPageCount);
	serialDebug.Write("\r\n");

	VirtAlloc virtualAllocator(
	    pageAllocator, UIntPtr(kernelOffset), pageAllocator.totalPageCount,
	    UIntPtr::From(kernelStartAddress), UIntPtr::From(kernelEndAddress),
	    kernelOffset, serialDebug);

	virtualAllocator.reserve(kernelOffset);
	// Reserve Page Table
	virtualAllocator.reserve(0xFFFF80000000A000, 1);
	virtualAllocator.reserve(0xFFFF80000000B000, 1);
	virtualAllocator.reserve(0xFFFF80000000C000, 1);
	virtualAllocator.reserve(0xFFFF80000000D000, 1);
	virtualAllocator.reserve(0xFFFF80000000E000, 1);
	virtualAllocator.reserve(0xFFFF80000000F000, 1);
	// Reserve Screen
	pageAllocator.reserve(0xFFFF8000000B8000, 1);

	PhysMap pageMap(&pageAllocator, UIntPtr::From(kernelStartAddress),
	                UIntPtr::From(kernelEndAddress), kernelOffset, serialDebug);
	pageMap.map(0, kernelOffset);

	auto physMem = pageAllocator.pages;
	auto virtMem = virtualAllocator.pages;
	auto mapMem  = pageMap.pages;
	// TODO: Assert true
	virtualAllocator.reserve(physMem.virt, physMem.count);
	// TODO: Assert true
	virtualAllocator.reserve(mapMem.virt, mapMem.count);
	// TODO: Assert true
	pageMap.map(physMem.phys, physMem.virt, physMem.count);
	// TODO: Assert true
	pageMap.map(virtMem.phys, virtMem.virt, virtMem.count);
	// TODO: Assert true
	pageMap.map(0xB8000, 0xFFFF8000000B8000, 1);

	PageTable pageTable(pageAllocator, virtualAllocator, pageMap,
	                    UIntPtr::From(kernelStartAddress),
	                    UIntPtr::From(kernelEndAddress), kernelOffset,
	                    serialDebug);
	pageTable.initMap(physMem.phys, physMem.virt, physMem.count);
	pageTable.initMap(virtMem.phys, virtMem.virt, virtMem.count);
	pageTable.initMap(mapMem.phys, mapMem.virt, mapMem.count);
	pageTable.initMap(0, 0xFFFF800000000000, 1);       // IDT
	pageTable.initMap(0xE000, 0xFFFF80000000E000, 2);  // Stack
	pageTable.initMap(0xB8000, 0xFFFF8000000B8000, 1); // Screen

	screen.rebase(reinterpret_cast<UInt8*>(0xFFFF8000000B8000));

	serial.Write("CR3: ");
	serial.WriteHex(CPU::GetCR3());
	serial.Write("\r\n");
	pageTable.activate();
	serial.Write("CR3: ");
	serial.WriteHex(CPU::GetCR3());
	serial.Write("\r\n");

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
	globalScreen->Write("\r");
	globalScreen->WriteHex(UIntPtr((++timerCount).value));
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
				globalScreen->Write(character);
			} else if (keycode == 0x2A) { // LShift
				shift = true;
			} else if (keycode == 0x1C) { // Enter
				globalScreen->Write("\r\n");
			} else if (keycode == 0x0E) { // Backspace
				globalScreen->Write(8);
			} else {
				globalScreen->WriteHex(keycode);
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

	globalScreen->Write("Got interrupt: ");
	globalScreen->WriteHex(UIntPtr(registers.interruptNumber.value));
	globalScreen->Write("\r\n");
}
}
