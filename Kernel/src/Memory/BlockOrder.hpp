#pragma once

#include <integers>

#define BlockOrderCount 12

enum class BlockOrder : UInt8::BackingType {
	_4k = 0,
	_8k,
	_16k,
	_32k,
	_64k,
	_128k,
	_256k,
	_512k,
	_1m,
	_2m,
	_4m,
	_8m,
};
