#pragma once

#include "types.h"

class Screen {
  public:
	Screen();
	~Screen();

	void WriteRaw(char);
	void WriteRaw(const char*);

  private:
	uint16_t x;
};
