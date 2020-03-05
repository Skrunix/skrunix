#pragma once

#include <integers>

struct PageBlock {
	PageBlock* next;
	UIntPtr    address;
};
