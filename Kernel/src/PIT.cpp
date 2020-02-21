#include "PIT.hpp"

#include "IO.hpp"

#define PIT_COMMAND 0x43
#define PIT_CH0_DATA 0x40
#define PIT_CH1_DATA 0x41
#define PIT_CH2_DATA 0x42
#define BEEP_COMMAND 0x61

#define CMD_CH0 (0b00 << 6)
#define CMD_CH1 (0b01 << 6)
#define CMD_CH2 (0b10 << 6)

#define CMD_ACCESS_LATCH (0b00 << 4)
#define CMD_ACCESS_LOW (0b01 << 4)
#define CMD_ACCESS_HIGH (0b10 << 4)
#define CMD_ACCESS_LOWHIGH (0b11 << 4)

#define CMD_OP_INTERRUPT (0b000 << 1)
#define CMD_OP_ONESHOT (0b001 << 1)
#define CMD_OP_RATEGEN (0b010 << 1)
#define CMD_OP_SQUAREWAVE (0b011 << 1)
#define CMD_OP_SOFTWARESTROBE (0b100 << 1)
#define CMD_OP_HARDWARESTROBE (0b101 << 1)
#define CMD_OP_RATEGEN2 (0b110 << 1)
#define CMD_OP_SQUAREWAVE2 (0b111 << 1)

#define CMD_16BIT (0b0)
#define CMD_4BCD (0b1)

PIT::PIT(UInt16 frequency) {
	uint16_t divisor = 1193180 / frequency.value;

	IO::out(PIT_COMMAND,
	        CMD_CH0 | CMD_ACCESS_LOWHIGH | CMD_OP_SQUAREWAVE | CMD_16BIT);
	IO::out(PIT_CH0_DATA, divisor & 0xFF);
	IO::out(PIT_CH0_DATA, (divisor >> 8) & 0xFF);
}

PIT::~PIT() {}

void PIT::Beep(UInt16 frequency) {
	uint16_t divisor = 1193180 / frequency.value;

	IO::out(PIT_COMMAND,
	        CMD_CH2 | CMD_ACCESS_LOWHIGH | CMD_OP_SQUAREWAVE | CMD_16BIT);
	IO::out(PIT_CH2_DATA, divisor & 0xFF);
	IO::out(PIT_CH2_DATA, (divisor >> 8) & 0xFF);

	UInt8 beepValue = IO::in(BEEP_COMMAND);
	IO::out(BEEP_COMMAND, beepValue | 3);
}

void PIT::Stop() {
	UInt8 beepValue = IO::in(BEEP_COMMAND);
	IO::out(BEEP_COMMAND, beepValue & 0xFC);
}
