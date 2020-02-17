#include "PIC.hpp"
#include "IO.hpp"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0XA1

#define PIC2_INDEX 2
#define PIC_INIT 0x11
#define PIC_OFFSET 0x20
#define PIC_8086 0x01

#define PIC_EOI 0x20

PIC::PIC() {
	// Program the PICs
	IO::out(PIC1_COMMAND, PIC_INIT);
	IO::out(PIC2_COMMAND, PIC_INIT);

	IO::out(PIC1_DATA, PIC_OFFSET);
	IO::out(PIC2_DATA, PIC_OFFSET + 8);

	IO::out(PIC1_DATA, 1 << PIC2_INDEX);
	IO::out(PIC2_DATA, PIC2_INDEX);

	IO::out(PIC1_DATA, PIC_8086);
	IO::out(PIC2_DATA, PIC_8086);

	// Mask all interrupts
	IO::out(PIC1_DATA, 0xFF);
	IO::out(PIC2_DATA, 0xFF);

	// FIXME: Enable timer/keyboard interrupt
	IO::out(PIC1_DATA, ~0x03);
}

PIC::~PIC() {}

void PIC::EOI1() { IO::out(PIC1_COMMAND, PIC_EOI); }
void PIC::EOI2() { IO::out(PIC2_COMMAND, PIC_EOI); }
