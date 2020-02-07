#include "Screen.hpp"

void main() {
	Screen screen;

	screen.SetForeground(Screen::Color::Blue);
	screen.setBackground(Screen::Color::LightRed);
	screen.WriteRaw("HELLO");

	screen.SetForeground(Screen::Color::Magenta);
	screen.setBackground(Screen::Color::Cyan);
	screen.WriteRaw('\0');
	for (char i = 1; i != 0; ++i) {
		screen.WriteRaw(i);
	}
}

extern "C" {
void kmainpp() { main(); }
}
