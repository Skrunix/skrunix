#pragma once

#include <stddef.h>

class PhysicalAllocatorInit {
  public:
	PhysicalAllocatorInit();
	~PhysicalAllocatorInit();

  private:
	PhysicalAllocatorInit(const PhysicalAllocatorInit&) = delete;
	PhysicalAllocatorInit& operator=(const PhysicalAllocatorInit&) = delete;

	static void* operator new(size_t)     = delete;
	static void* operator new[](size_t)   = delete;
	static void  operator delete(void*)   = delete;
	static void  operator delete[](void*) = delete;
};
