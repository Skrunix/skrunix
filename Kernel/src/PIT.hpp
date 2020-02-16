#pragma once

#include <stdint.h>

class PIT {
  public:
	PIT(uint16_t frequency);
	~PIT();
};
