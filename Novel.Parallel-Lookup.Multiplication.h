/*
Q:What is the computational complexity of a multiplication algorithm that computes all partial products in parallel, O(1), in-place, 
in the final product array, and then traverses from the LSB to the MSB using a lookup table to compute the add- with carry- for the final product, 
O(M + N), `Z[zIdx] = AddCarryLookup[Z[mIdx]][Z[nIdx]]; Where -1 < zIdx < M + N + 1; -1 < mIdx < M + 1; M + N - 1 < nIdx < M + N + 1`? N is incremented every N%M == 0. 
Initially, Z's total length supports all partial products which need an add-plus-carry computed.

A:The multiplication algorithm you described computes all partial products in parallel 
(O(1)) and then traverses from the least significant bit (LSB) to the most significant bit (MSB) 
using a lookup table to compute the add-with-carry operation (O(M + N)). The overall complexity 
of this algorithm is dominated by the second step, which has a complexity of O(M + N).

However, the assumption of computing all partial products in parallel with O(1) complexity 
is not practical for general-purpose computing systems, as it requires an extremely high level of parallelism. 
In reality, the number of processing units available for parallel computation is limited by the hardware, 
and it is not possible to achieve O(1) complexity for calculating all partial products simultaneously.

Assuming that you have limited parallelism, the actual complexity of computing all partial products would be greater than O(1), 
which would increase the overall complexity of the algorithm. The complexity of this step depends on the level of parallelism you can achieve in practice.

In summary, the proposed algorithm's complexity is O(M + N) based on the assumption of computing all partial products in parallel with O(1) complexity. 
However, in practice, this assumption is not achievable with general-purpose computing systems, and the overall complexity would be higher, 
depending on the level of parallelism available.
ahshabazz2017@gmail.com
What would be a proper or trendy name for this algorithm (eg. Zipper multiplication, wide-span multiplication, Flat multiplication, ... etc.)?

Given the unique features of the algorithm you described, such as computing partial products in parallel and using a lookup table to perform add-with-carry operations, 
an appropriate name could be "Parallel-Lookup Multiplication." This name highlights the parallelism aspect and the use of a lookup table for the addition step.

Alternatively, you can choose other names based on the features or properties of the algorithm that you find most distinctive or appealing. Some suggestions include:

    High-Parallel Multiplication
    Carry-Lookup Multiplication
    Concurrent-Sum Multiplication

Remember that the name should ideally reflect the key features or concepts of the algorithm, making it easier for others to understand its functionality and remember it.
*/

// Parallel-Lookup Multiplication

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <numeric>

class BigInt
{
public:
    BigInt(const std::string& num_str)
	{
        for (auto it = num_str.rbegin(); it != num_str.rend(); ++it)
		{
            digits_.push_back(*it - '0');
        }
    }

    const std::vector<int>& get_digits() const
	{
        return digits_;
    }

private:
    std::vector<int> digits_;
};

void compute_partial_product(const BigInt& M, int digit_N, int index_N, std::vector<int>& product)
{
    const auto& M_digits = M.get_digits();
    int carry = 0;

    for (size_t i = 0; i < M_digits.size(); ++i)
	{
        int mul = M_digits[i] * digit_N + carry + product[i + index_N];
        product[i + index_N] = mul % 10;
        carry = mul / 10;
    }

    if (carry > 0)
	{
        product[M_digits.size() + index_N] = carry;
    }
}

std::vector<int> parallel_lookup_multiplication(const BigInt& M, const BigInt& N)
{
    size_t M_len = M.get_digits().size();
    size_t N_len = N.get_digits().size();

    std::vector<int> product(M_len * N_len, 0);
    std::vector<std::thread> threads;

    for (size_t i = 0; i < N_len; ++i)
	{
        threads.emplace_back([&M, &N, i, &product]()
		{
            compute_partial_product(M, N.get_digits()[i], i, product);
        });
    }

    for (auto& t : threads)
	{
        t.join();
    }

    return product;
}


// Version 2: Parallel-Lookup Multiplication (Add by column (no carry))

std::vector<int> parallel_lookup_multiplication(const BigInt& M, const BigInt& N) {
    size_t M_len = M.get_digits().size();
    size_t N_len = N.get_digits().size();
    size_t product_len = M_len + N_len;

    std::vector<int> product(product_len, 0);
    std::vector<std::thread> threads;

    // Intermediate Step 1: Sum all intermediate products by column
    for (size_t col = 0; col < product_len - 1; ++col) {
        threads.emplace_back([&M, &N, col, &product]() {
            int column_sum = 0;

            for (size_t m = 0; m <= col; ++m) {
                size_t n = col - m;
                if (m < M.get_digits().size() && n < N.get_digits().size()) {
                    column_sum += M.get_digits()[m] * N.get_digits()[n];
                }
            }

            product[col] = column_sum;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // Intermediate Step 2: Adjust for the number of carries, without computing the carry itself
    for (size_t i = 0; i < product.size() - 1; ++i) {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    // Remove leading zeros
    while (product.back() == 0) {
        product.pop_back();
    }

    return product;
}

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
    BigInt(const std::string& num_str) {
        for (auto it = num_str.rbegin(); it != num_str.rend(); ++it) {
            digits_.push_back(*it - '0');
        }
    }

    const std::vector<int>& get_digits() const {
        return digits_;
    }

private:
    std::vector<int> digits_;
};

void compute_column_sum(const BigInt& M, const BigInt& N, size_t col, std::vector<int>& product) {
    int column_sum = 0;

    for (size_t m = 0; m <= col; ++m) {
        size_t n = col - m;
        if (m < M.get_digits().size() && n < N.get_digits().size()) {
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

std::vector<int> parallel_lookup_multiplication(const BigInt& M, const BigInt& N) {
    size_t M_len = M.get_digits().size();
    size_t N_len = N.get_digits().size();
    size_t product_len = M_len + N_len;

    std::vector<int> product(product_len, 0);
    std::vector<std::jthread> threads(M_len + N_len);

    std::latch work_latch(M_len + N_len);
    std::barrier work_barrier(M_len + N_len + 1);

    // Create a thread pool of M + N threads
    for (size_t i = 0; i < M_len + N_len; ++i) {
        threads[i] = std::jthread([&](std::stop_token stoken) {
            while (!stoken.stop_requested()) {
                work_latch.wait(stoken);
                if (i < product_len - 1) {
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
    for (size_t i = 0; i < product.size() - 1; ++i) {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    // Remove leading zeros
    while (product.back() == 0) {
        product.pop_back();
    }

    // Signal threads to stop
    for (auto& t : threads) {
        t.request_stop();
    }

    return product;
}

int main() {
    BigInt M("123");
    BigInt N("456");

    auto product = parallel_lookup_multiplication(M, N);

    // Reverse the digits and print the result
    std::reverse(product.begin(), product.end());
    for (const auto& digit : product) {
        std::cout << digit;
    }
    std::cout << std::endl;

    return 0;
}


int main()
{
    BigInt M("123");
    BigInt N("456");

    auto product = parallel_lookup_multiplication(M, N);

    // Remove leading zeros
    while (product.back() == 0)
	{
        product.pop_back();
    }

    // Reverse the digits and print the result
    std::reverse(product.begin(), product.end());
    for (const auto& digit : product)
	{
        std::cout << digit;
    }
    std::cout << std::endl;

    return 0;
}

//
