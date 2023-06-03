#include <iostream>
#include <cstdint>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>

void profiler (std::function<void()> f)
{
	auto start_time_chrono = std::chrono::high_resolution_clock::now ();
	
	f();
	
	std::cout << std::endl;
	auto end_time_chrono = std::chrono::high_resolution_clock::now();
	auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>( end_time_chrono - start_time_chrono ).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << "\n\n";
}

int main ()
{
	profiler([&]()
	{
		std::vector<std::string> a{{"hat"},{"mat"},{"cat"},{"bat"},{"five"}};
		for(const std::string& str : a)
		{
			std::ranges::copy(std::vector<char> {str.begin(),str.end()}, std::ostream_iterator<int>(std::cout, " "));
		}
		std::cout << "\nBuiltin Model";
	});
	
	return EXIT_SUCCESS;
}

/*
Output: 
104 97 116 109 97 116 99 97 116 98 97 116 102 105 118 101 
Builtin Model
Total Duration (nanoseconds): 69581
*/
