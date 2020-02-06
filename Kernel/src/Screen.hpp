#pragma once

#include "types.h"

class Screen {
public:
	Screen();
	~Screen();
	
	void WriteRaw(char);
private:
	uint8_t x;
};
