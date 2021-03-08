#pragma once

#include <stddef.h>

class PhysicalAllocator {
  private:
	PhysicalAllocator(const PhysicalAllocator&) = delete;
	PhysicalAllocator& operator=(const PhysicalAllocator&) = delete;

	~PhysicalAllocator() = delete;

	static void* operator new(size_t)     = delete;
	static void* operator new[](size_t)   = delete;
	static void  operator delete(void*)   = delete;
	static void  operator delete[](void*) = delete;
};
