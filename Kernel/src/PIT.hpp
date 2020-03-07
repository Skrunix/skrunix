#pragma once

#include <Integers/Integers.hpp>

class PIT {
  public:
	PIT(UInt16 frequency);
	~PIT();

	void Beep(UInt16 frequency);
	void Stop();
};
