


// Version 3: Parallel-Lookup Multiplication (Add by column (no carry)) w/ thread pool
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <numeric>
#include <latch>
#include <barrier>

class BigInt {
public:
    BigInt(const std::string& num_str)
    {
        for (auto it = num_str.rbegin(); it != num_str.rend(); ++it)
        {
            if (*it >= '0' && *it <= '9')
            {
                digits_.push_back(*it - '0');
            }
            else if (*it == '-')
            {
                sign_ = -1;
            }
        }
        if (digits_.empty())
        {
            digits_.push_back(0);
        }
    }
    const std::vector<int>& get_digits() const
    {
        return digits_;
    }

private:
    std::vector<int> digits_;
    int sign_ = 1;
};

void compute_column_sum(const BigInt& M, 
    const BigInt& N, 
    size_t col, 
    std::vector<int>& product)
{
    int column_sum = 0;

    for (size_t m = 0; m <= col; ++m)
    {
        size_t n = col - m;
        if (m < M.get_digits().size() && n < N.get_digits().size())
        {
            column_sum += M.get_digits()[m] * N.get_digits()[n];
        }
    }

    product[col] = column_sum;
}

/*
A:In this implementation, a fixed-size thread pool of M + N threads is created using std::jthread. 
A std::latch is used to synchronize the work distribution among threads and a std::barrier is used 
to ensure all threads have completed their tasks before proceeding to Intermediate Step 2.

Here's a brief overview of the updated parallel_lookup_multiplication function:

    Create a vector of std::jthread objects with a size of M + N.
    Initialize a std::latch with an initial count of M + N.
    Initialize a std::barrier with a participant count of M + N + 1 (the extra participant is the main thread).
    Spawn M + N threads and make them wait on the std::latch and std::barrier.
    In Intermediate Step 1, count down the latch to trigger the threads to start working, 
    	and wait on the barrier to ensure all threads have completed their tasks.
    Perform Intermediate Step 2 in the main thread.
    Request all threads to stop, and return the product.

This implementation uses a fixed-size thread pool to manage the parallel execution of tasks, 
which improves the efficiency of the algorithm compared to the previous version that spawned a separate thread for each column. 
The overall computational complexity is still O(M + N) due to Intermediate Step 2, 
but the parallel execution of Intermediate Step 1 with a thread pool should result in better performance.
*/

std::vector<int> parallel_multiplication(const BigInt& M, const BigInt& N)
{
    size_t M_len = M.get_digits().size();
    size_t N_len = N.get_digits().size();
    size_t product_len = M_len + N_len;

    std::vector<int> product(product_len, 0);
    std::vector<std::jthread> threads(M_len + N_len);

    std::latch work_latch(M_len + N_len);
    std::barrier work_barrier(M_len + N_len + 1);

    // Create a thread pool of M + N threads
    for (size_t i = 0; i < M_len + N_len; ++i)
    {
        threads[i] = std::jthread([&](std::stop_token stoken)
        {
            while (!stoken.stop_requested())
            {
                work_latch.wait(stoken);
                if (i < product_len - 1) 
                {
                    compute_column_sum(M, N, i, product);
                }
                work_barrier.arrive_and_wait(stoken);
            }
        });
    }

    // Intermediate Step 1: Sum all intermediate products by column
    work_latch.count_down(M_len + N_len);
    work_barrier.arrive_and_wait();

    // Intermediate Step 2: Adjust for the number of carries, without computing the carry itself
    for (size_t i = 0; i < product.size() - 1; ++i)
    {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    // Remove leading zeros
    while (product.back() == 0)
    {
        product.pop_back();
    }

    // Signal threads to stop
    for (auto& t : threads)
    {
        t.request_stop();
    }

    return product;
}

int main() {
    BigInt M("123");
    BigInt N("456");

    auto product = parallel_multiplication(M, N);

    // Reverse the digits and print the result
    std::reverse(product.begin(), product.end());
    for (const auto& digit : product) {
        std::cout << digit; // 56088
    }
    std::cout << std::endl;

    return 0;
}

// Todo: Fix lookup table implementation, which requires size( Max(M, N) )