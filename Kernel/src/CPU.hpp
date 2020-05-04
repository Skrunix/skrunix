#pragma once

#include <Integers/Integers.hpp>

struct CPU {
	static UIntPtr GetCR3();
	static void    SetCR3(UIntPtr);
};
