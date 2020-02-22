#pragma once

#include <integers>

class Serial {
  public:
	Serial();
	~Serial();

	void Write(char);
	void Write(const char*);

	void WriteHex(UInt64);

  private:
	bool CanWrite();
};
