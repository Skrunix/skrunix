#pragma once

#include <Boolean/Boolean.hpp>
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

	void WriteFormat(const char*, UIntPtr);

  private:
	Bool CanWrite();
};
