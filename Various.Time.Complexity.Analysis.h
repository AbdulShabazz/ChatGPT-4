
//#include "../boost/multiprecision/cpp_int.hpp"
//#include "../EuclidProverLibDLL/EuclidProverLibDLL.h"
//#include "../EuclidProverLibDLL/TestCases.h"

#include <vector>
#include <chrono>
#include <iostream>
#include <ppl.h> // Include the Parallel Patterns Library
#include <thread>

void CalculateSquares(const std::vector<int>&input, std::vector<int>&output)
{
    // Use parallel_for to perform the calculation concurrently
    /*concurrency::parallel_for(size_t(0), input.size(), [&](size_t i) // < 805106000 ns
        {
        output.at(i) = input.at(i) * input.at(i);
        });*/
    const size_t I = input.size();
    for (size_t i = 0; i < I; ++i) // < 403202000 ns
    {
        output[i] = input[i] * input[i];
    }
}

int main()
{
	//using namespace EuclidProverLib;

	// Instantiate Prover (module)
	/*EuclidProver<BracketType::CurlyBraces> Euclid{};

	const std::vector<std::string>& axiom_0 = { "{", "1", "}","+","{", "1", "}","=","{", "2", "}" };
	Euclid.Axiom( axiom_0 );*/

	//x86i64IntTestCases{};
	/*
	using namespace boost::multiprecision;
	// Repeat at arbitrary precision:
	cpp_int u = 1;
	for (unsigned i = 1; i <= 100; ++i)
		u *= i;

	// prints 93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000 (i.e. 100!)
	std::cout << u << std::endl;
	*/;

    std::vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> output(input.size());
    std::vector<std::jthread> workers;
    //std::vector<std::thread> workers;

    //auto start_time_op = std::chrono::high_resolution_clock::now();
    /*
    const size_t I = 100;
    for(size_t i = 0; i < 1e8; ++i) // < 4326113500 ns
    {
        CalculateSquares(input, output);
    }*/
    //CalculateSquares(input, output); // < 800 ns
    //workers.emplace_back([&input, &output]() {CalculateSquares(input, output); }); // < 15112000 ns
    //const size_t I = output.size();
    //for (size_t i = 0; i < I; ++i) // < 4526300 ns
    //{
    //    workers.emplace_back([&input, &output,i]() { output.at(i) = input.at(i) * input.at(i); });
    //}
    auto start_time_op = std::chrono::high_resolution_clock::now();
    workers.emplace_back([&input, &output]() {CalculateSquares(input, output); }); // < 25788800 ns 
    // join threads to ensure they have finished
    /*for (auto& t : workers) {
        t.join();
    } */  
    auto end_time_op = std::chrono::high_resolution_clock::now();
    auto duration_op = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_op - start_time_op).count();
    std::cout << "CalculateSquares(...) duration: " << duration_op << "_ns" << std::endl;

    std::cout << "Input: ";
    for (const int& val : input) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Output: ";
    for (const int& val : output) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

	return 0;
}