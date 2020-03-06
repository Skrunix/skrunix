#pragma once

#include <Integers.hpp>

struct PageBlock {
	PageBlock* next;
	UIntPtr    address;
};
