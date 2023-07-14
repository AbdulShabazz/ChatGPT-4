#include <iostream>

constexpr std::size_t hash_str(std::string_view str) {
	const std::size_t seed = 0xEA35D32C643E04EB;
	std::size_t d = (0xCBF29CE484222325 ^ seed) * static_cast<size_t>(0x100000001B3);

	for (const char& c : str)
		d = (d ^ static_cast<size_t>(c)) * static_cast<size_t>(0x01000193);

	return d >> 8;

}
