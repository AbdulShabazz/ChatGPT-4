#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <chrono>

int main()
{
	std::unordered_map<
	std::string,
	std::unordered_map<
	uint64_t,
	std::unordered_map<
	uint64_t,bool>>>
	
	InAxiomCallGraph_Map;
	
	InAxiomCallGraph_Map.emplace
	(
		"rhs_reduce", 
		std::unordered_map<
		uint64_t, 
		std::unordered_map<
		uint64_t,bool>> 
		{{0, {{0, true}} }}
	);
	
	InAxiomCallGraph_Map.reserve(10000);
	
	const auto start_time_chrono = std::chrono::high_resolution_clock::now();
	
	InAxiomCallGraph_Map["_reduce"][0][0];
	
	std::cout << "Hello World" << std::endl;

	const auto end_time_chrono = std::chrono::high_resolution_clock::now();
	const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;

	return EXIT_SUCCESS;
}
