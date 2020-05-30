#pragma once

#include <Integers/Integers.hpp>

class Screen {
  public:
	Screen(UInt8* base);
	Screen(const Screen&) = delete;
	~Screen();

	Screen& operator=(const Screen&) = delete;

	void rebase(UInt8* base);

	void Clear();
	void ScrollUp();

	void Write(char);
	void Write(const char*);

	void WriteHex(UInt8);
	void WriteHex(UIntPtr);

	void WriteRaw(char);
	void WriteRaw(const char*);

	enum class Color : UInt8::BackingType {
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
	UInt8* basePointer;

	UInt16 x;
	UInt16 y;

	UInt16 maxX;
	UInt16 maxY;

	Color foreground;
	Color background;

	void IncrementY();

	void MoveCursor(UInt16 newX, UInt16 newY);
	void UpdateCursor();
};
