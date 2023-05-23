#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <cmath>
#include <chrono>

int main()
{
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
	
	std::size_t base = 1234567890123456789;
    std::size_t exp = 1234567890123456789;

	auto start_time_chrono = std::chrono::high_resolution_clock::now();
    pow(base, exp);
    auto end_time_chrono = std::chrono::high_resolution_clock::now();
    auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>( end_time_chrono - start_time_chrono ).count();
    std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
    
    start_time_chrono = std::chrono::high_resolution_clock::now();
    Power(base,exp);
    end_time_chrono = std::chrono::high_resolution_clock::now();
    duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>( end_time_chrono - start_time_chrono ).count();
    std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
	
    
    return EXIT_SUCCESS;
}
