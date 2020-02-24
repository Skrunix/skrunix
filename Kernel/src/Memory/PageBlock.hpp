#pragma once

#include <integers>

struct PageBlock {
	PageBlock* next;
	UInt64     address;
};
