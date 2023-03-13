
#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

uint64_t sum_array(const std::vector<uint64_t>& array)
{
    const size_t num_threads = std::thread::hardware_concurrency();
    const size_t chunk_size = array.size() / num_threads;

    std::vector<uint64_t> intermediate_results(num_threads);
    std::vector<std::thread> threads(num_threads);

    for (size_t i = 0; i < num_threads; ++i)
    {
        const auto begin = array.begin() + i * chunk_size;
        const auto end = (i == num_threads - 1) ? array.end() : begin + chunk_size;

        threads[i] = std::thread([&, i, begin, end] {
            intermediate_results[i] = std::reduce(std::execution::par, begin, end);
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return std::reduce(std::execution::par, intermediate_results.begin(), intermediate_results.end());
}
