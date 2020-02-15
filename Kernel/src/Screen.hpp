#pragma once

#include <stdint.h>

class Screen {
  public:
	Screen();
	~Screen();

	void Clear();
	void ScrollUp();

	void Write(char);
	void Write(const char*);

	void WriteHex(uint8_t);
	void WriteHex(uintptr_t);

	void WriteRaw(char);
	void WriteRaw(const char*);

	enum class Color : uint8_t {
		Black        = 0x0,
		Blue         = 0x1,
		Green        = 0x2,
		Cyan         = 0x3,
		Red          = 0x4,
		Magenta      = 0x5,
		Brown        = 0x6,
		LightGray    = 0x7,
		DarkGray     = 0x8,
		LighBlue     = 0x9,
		LightGreen   = 0xA,
		LighCyan     = 0xB,
		LightRed     = 0xC,
		LightMagenta = 0xD,
		Yellow       = 0xE,
		White        = 0xF,
	};

	void SetForeground(Color);
	void setBackground(Color);

  private:
	uint16_t x;
	uint16_t y;

	uint16_t maxX;
	uint16_t maxY;

	Color foreground;
	Color background;

	void IncrementY();

	void MoveCursor(uint16_t newX, uint16_t newY);
	void UpdateCursor();
};
