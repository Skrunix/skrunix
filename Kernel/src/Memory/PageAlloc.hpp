#pragma once

#include "Debug.hpp"

#include <Integers/Integers.hpp>

#define PageShift 12
#define PageSize 4096

struct PageBlock {
	PageBlock* next;
	UIntPtr    address;
};

class PageAlloc {
  public:
	PageAlloc(const char* allocName, const Debug& debugObj);

	PageAlloc(const PageAlloc&) = delete;
	PageAlloc& operator=(const PageAlloc&) = delete;

	UIntPtr alloc(USize count = 1);
	void    free(UIntPtr address, USize count = 1);
	bool    reserve(UIntPtr address, USize count = 1);

	const char*  name;
	const Debug& debug;

	USize freePageCount;
	USize totalPageCount;

	PageBlock* freeBlocks;
	PageBlock* usedBlocks;

  protected:
	~PageAlloc();

	static void* operator new(size_t)     = delete;
	static void* operator new[](size_t)   = delete;
	static void  operator delete(void*)   = delete;
	static void  operator delete[](void*) = delete;
};
