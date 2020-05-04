#pragma once

#include <Integers/Integers.hpp>

struct ContiguousPages {
	UIntPtr phys;
	UIntPtr virt;
	USize count;
};
