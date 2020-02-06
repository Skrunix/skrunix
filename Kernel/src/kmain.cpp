#include "Screen.hpp"

extern "C" void PrintString64(int offset, const char* string);

void main() {
	PrintString64(0, "Kernel in C++!");
	
	Screen screen;
	screen.WriteRaw(0);
	for (char i = 1; i != 0; ++i) {
		screen.WriteRaw(i);
	}
}

extern "C" {
	void kmainpp() {
		main();
	}
}
