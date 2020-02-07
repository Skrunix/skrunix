#include "Screen.hpp"

void main() {
	Screen screen;
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
			screen.SetForeground((Screen::Color)fg);
			screen.setBackground((Screen::Color)bg);
			screen.WriteRaw('E');
		}
	}
}

extern "C" {
void kmainpp() { main(); }
}
