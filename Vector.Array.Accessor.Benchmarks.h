#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    constexpr size_t num_iterations = 1'000'000'000;
    std::vector<uint64_t> a(2), b(2);

    // Benchmark operator[]
    auto start_time_op = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_iterations; ++i) {
        a[0] = 1;
    }
    auto end_time_op = std::chrono::high_resolution_clock::now();
    auto duration_op = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_op - start_time_op).count();

    // Benchmark at()
    auto start_time_at = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_iterations; ++i) {
        b.at(1) = 1;
    }
    auto end_time_at = std::chrono::high_resolution_clock::now();
    auto duration_at = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_at - start_time_at).count();

    std::cout << "operator[] duration: " << duration_op << " ns" << std::endl;
    std::cout << "at() duration: " << duration_at << " ns" << std::endl;

    return 0;
}
