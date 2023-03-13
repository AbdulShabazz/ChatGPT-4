
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

void parallelSum(const std::vector<uint64_t>& input,
                 std::vector<uint64_t>& output,
                 uint64_t start,
                 uint64_t end)
{
    if (start == end)
    {
        output[start] = input[start];
        return;
    }

    uint64_t mid = (start + end) / 2;
    std::vector<uint64_t> left_output(mid - start + 1);
    std::vector<uint64_t> right_output(end - mid);

    std::vector<std::future<uint64_t>> futures;
    futures.push_back(std::async(std::launch::async, [&input, &left_output, start, mid] {
        return std::reduce(std::execution::par, input.begin() + start, input.begin() + mid + 1, uint64_t(0));
    }));
    futures.push_back(std::async(std::launch::async, [&input, &right_output, mid, end] {
        return std::reduce(std::execution::par, input.begin() + mid + 1, input.begin() + end + 1, uint64_t(0));
    }));

    output[start] = futures[0].get();
    output[mid + 1] = futures[1].get();

    std::partial_sum(output.begin() + start, output.begin() + mid + 2, output.begin() + start);
    std::partial_sum(output.begin() + mid + 1, output.begin() + end + 1, output.begin() + mid + 1);
}

/*
Q:Can the performance of the completion be further improved, such as with recursive paralleSum calls, or with an equivalent while-loop?

A:Yes, it's possible to further improve the performance of the parallelSum function by using recursive calls or an equivalent while-loop.

One approach is to replace the recursive calls with a loop that processes subarrays in parallel until the size of the subarray falls below a certain threshold. 
This is called "work stealing" and is a common technique used to balance the load across threads.

Here's an example implementation of parallelSum using a while-loop:
*/

void parallelSum(const std::vector<uint64_t>& input,
                 std::vector<uint64_t>& output,
                 uint64_t start,
                 uint64_t end)
{
    const uint64_t threshold = 1000;

    std::vector<std::pair<uint64_t, uint64_t>> stack;
    stack.emplace_back(start, end);

    while (!stack.empty()) {
        auto [lo, hi] = stack.back();
        stack.pop_back();

        if (hi - lo + 1 <= threshold) {
            output[lo] = std::reduce(std::execution::par, input.begin() + lo, input.begin() + hi + 1, uint64_t(0));
        } else {
            uint64_t mid = (lo + hi) / 2;
            std::vector<std::future<void>> futures;
            futures.push_back(std::async(std::launch::async, [&input, &output, lo, mid] {
                parallelSum(input, output, lo, mid);
            }));
            futures.push_back(std::async(std::launch::async, [&input, &output, mid + 1, hi] {
                parallelSum(input, output, mid + 1, hi);
            }));
            for (auto& future : futures) {
                future.wait();
            }

            std::partial_sum(output.begin() + lo, output.begin() + mid + 1, output.begin() + lo);
            std::partial_sum(output.begin() + mid + 1, output.begin() + hi + 1, output.begin() + mid + 1);
        }
    }
}

/*
A:This implementation replaces the recursive calls with a while-loop that maintains a stack of subarrays to process. 
If the size of the subarray falls below the threshold, the function uses std::reduce to compute the sum of the elements in the subarray. 
Otherwise, it splits the subarray in two and recursively calls parallelSum on each subarray in parallel. 
The function then uses std::partial_sum to compute the cumulative sums of the left and right subarrays.

The threshold value used in this implementation can be adjusted to balance the overhead of splitting and merging subarrays with the benefits of parallelization.

Overall, the performance of the parallelSum function can be improved by using work stealing or a similar technique to balance the load across threads, 
and by choosing appropriate threshold values to optimize the parallelization overhead.
*/

bool parallelArraySum(const std::vector<uint64_t>& input)
{
    std::vector<uint64_t> output(input.size());
    parallelSum(input, output, 0, input.size() - 1);
    return true;
}
