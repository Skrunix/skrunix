#pragma once

#include <Integers/Integers.hpp>

struct PageBlock {
	PageBlock* next;
	UIntPtr    address;
};
