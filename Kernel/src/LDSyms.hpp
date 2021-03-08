#pragma once

#include <Integers/Integers.hpp>

class Nothing {
  private:
	Nothing()  = delete;
	~Nothing() = delete;
};

extern Nothing _KernelOffset;
extern Nothing _KernelStart;
extern Nothing _KernelEnd;

constexpr UIntPtr KernelOffset() { return UIntPtr::From(&_KernelOffset); }
constexpr UIntPtr KernelStart() { return UIntPtr::From(&_KernelStart); }
constexpr UIntPtr KernelEnd() { return UIntPtr::From(&_KernelEnd); }

extern Nothing _KernelTextStart;
extern Nothing _KernelTextSize;

constexpr UIntPtr KernelTextStart() { return UIntPtr::From(&_KernelTextStart); }
constexpr UIntPtr KernelTextSize() { return UIntPtr::From(&_KernelTextSize); }

extern Nothing _KernelRODataStart;
extern Nothing _KernelRODataSize;

constexpr UIntPtr KernelRODataStart() {
	return UIntPtr::From(&_KernelRODataStart);
}
constexpr UIntPtr KernelRODataSize() {
	return UIntPtr::From(&_KernelRODataSize);
}
extern Nothing _KernelDataStart;
extern Nothing _KernelDataSize;

constexpr UIntPtr KernelDataStart() { return UIntPtr::From(&_KernelDataStart); }
constexpr UIntPtr KernelDataSize() { return UIntPtr::From(&_KernelDataSize); }

extern Nothing _KernelBSSStart;
extern Nothing _KernelBSSSize;

constexpr UIntPtr KernelBSSStart() { return UIntPtr::From(&_KernelBSSStart); }
constexpr UIntPtr KernelBSSSize() { return UIntPtr::From(&_KernelBSSSize); }

extern Nothing _KernelRemoveAfterPagingStart;
extern Nothing _KernelRemoveAfterPagingSize;

constexpr UIntPtr KernelRemoveAfterPagingStart() {
	return UIntPtr::From(&_KernelRemoveAfterPagingStart);
}
constexpr UIntPtr KernelRemoveAfterPagingSize() {
	return UIntPtr::From(&_KernelRemoveAfterPagingSize);
}
