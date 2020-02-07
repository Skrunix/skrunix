#include "Screen.hpp"

void main() {
	Screen screen;

	screen.WriteRaw("HELLO");

	screen.WriteRaw('\0');
	for (char i = 1; i != 0; ++i) {
		screen.WriteRaw(i);
	}
}

extern "C" {
void kmainpp() { main(); }
}
