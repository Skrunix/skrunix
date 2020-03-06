#pragma once

namespace std {

template <class T, T V>
struct integral_constant {
	static constexpr T value = V;

	constexpr operator T() const noexcept { return value; }

	constexpr T operator()() const noexcept { return value; }
};

} // namespace std
