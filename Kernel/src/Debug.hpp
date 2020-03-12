#pragma once

#include <Integers/Integers.hpp>

struct Debug {
	Debug(void (*writeFunction)(char));
	~Debug();

	void Write(char) const;
	void Write(const char*) const;

	void WriteHex(UInt32) const;
	void WriteHex(UIntPtr) const;
	void WriteHex(USize) const;

  private:
	void (*write)(char);
};
