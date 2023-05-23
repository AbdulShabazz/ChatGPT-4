
auto Power = [] (std::size_t base, std::size_t exponent) -> std::size_t {
	std::size_t result = 1;
	while (exponent > 0) {
		// If exponent is odd
		if (exponent & 1) {
			result = result * base;
		}
		// halve the exponent
		exponent = exponent >> 1;
		base = base * base;
	}
	return result;
};
