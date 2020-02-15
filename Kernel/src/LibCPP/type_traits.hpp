#pragma once

namespace std {

template <class Type> struct underlying_type {
	typedef __underlying_type(Type) type;
};

} // namespace std
