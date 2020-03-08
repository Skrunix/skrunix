#pragma once

#include <Integers/Integers.hpp>

class Serial {
  public:
	Serial();
	~Serial();

	void Write(char);
	void Write(const char*);

	void WriteHex(UInt32);
	void WriteHex(UInt64);
	void WriteHex(UIntPtr);

  private:
	bool CanWrite();
};
