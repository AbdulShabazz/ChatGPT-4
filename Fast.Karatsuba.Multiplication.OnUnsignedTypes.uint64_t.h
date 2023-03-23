/*
Q:Refactor the c++20 std::string Karatsuba algorithm to implement `std::vector<uint64_t>` to store and multiply the input integers.

A:Here's a refactored version of the Karatsuba algorithm using std::vector<uint64_t> to store and multiply the input integers:

cpp 
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstdint>

class BigIntMultiplier
{
private:
	std::vector<uint64_t> num1, num2;
	const uint64_t base = 1e9;

	std::vector<uint64_t> add(const std::vector<uint64_t> &a, const std::vector<uint64_t> &b)
	{
		std::vector<uint64_t> result(std::max(a.size(), b.size()) + 1);
		uint64_t carry = 0;

		for (size_t i = 0; i < result.size(); ++i)
		{
			uint64_t sum = carry;
			if (i < a.size()) sum += a[i];
			if (i < b.size()) sum += b[i];

			carry = sum / base;
			result[i] = sum % base;
		}

		while (result.size() > 1 && result.back() == 0)
			result.pop_back();
		return result;
	}

	std::vector<uint64_t> subtract(const std::vector<uint64_t> &a, const std::vector<uint64_t> &b)
	{
		std::vector<uint64_t> result(a.size());
		int64_t carry = 0;

		for (size_t i = 0; i < result.size(); ++i)
		{
			int64_t diff = a[i] - carry;
			if (i < b.size()) 
				diff -= b[i];

			if (diff < 0)
			{
				carry = 1;
				diff += base;
			}
			else
			{
				carry = 0;
			}

			result[i] = diff;
		}

		while (result.size() > 1 && result.back() == 0) result.pop_back();
		return result;
	}

	std::vector<uint64_t> multiply(const std::vector<uint64_t> &a, 
	const std::vector<uint64_t> &b)
	{
		if (a.size() <= 1 || b.size() <= 1)
		{
			uint64_t prod = 0;
			if (!a.empty() && !b.empty()) prod = a[0] * b[0];
			return {prod / base, prod % base};
		}

		size_t n = std::max(a.size(), b.size());
		size_t half = n / 2;

		std::vector<uint64_t> a1(a.begin(), a.begin() + half);
		std::vector<uint64_t> a0(a.begin() + half, a.end());
		std::vector<uint64_t> b1(b.begin(), b.begin() + half);
		std::vector<uint64_t> b0(b.begin() + half, b.end());

		std::vector<uint64_t> z2 = multiply(a1, b1);
		std::vector<uint64_t> z1 = multiply(add(a1, a0), add(b1, b0));
		std::vector<uint64_t> z0 = multiply(a0, b0);

		for (size_t i = 0; i < 2 * half; ++i)
			z2.push_back(0);
		for (size_t i = 0; i < half; ++i)
			z1.push_back(0);

		return add(add(z2, z1), z0);
	}

	std::vector<uint64_t> str_to_vec(const std::string &num)
	{
		std::vector<uint64_t> result;
		for (int i = num.size(); i > 0; i -= 9)
		{
			int start = std::max(i - 9, 0);
			std::string segment = num.substr(start, i - start);
			result.push_back(std::stoull(segment));
		}
		while (result.size() > 1 && result.back() == 0)
			result.pop_back();
		return result;
	}

	std::string vec_to_str(const std::vector<uint64_t> &num)
	{
		std::string result;
		for (const auto &digit : num)
		{
			result = std::to_string(digit) + result;
		}

		return result.empty() ? "0" : result;
	}

public:
	BigIntMultiplier(const std::string &number1, const std::string &number2)
	{
	if (!std::all_of(number1.begin(), number1.end(), ::isdigit) ||
	!std::all_of(number2.begin(), number2.end(), ::isdigit))
	{
		throw std::invalid_argument("Both input strings must be valid non-negative integers.");
	}
		num1 = str_to_vec(number1);
		num2 = str_to_vec(number2);
	}

	std::string multiply()
	{
		std::vector<uint64_t> product = multiply(num1, num2);
		return vec_to_str(product);
	}

};

int main()
{
	std::string num1 = "123456789012345678901234567890";
	std::string num2 = "987654321098765432109876543210";


	try {
		BigIntMultiplier multiplier(num1, num2);
		std::string result = multiplier.multiply();
		std::cout << "Result: " << result << std::endl;
	} catch (std::invalid_argument &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}

/* 
A:In this implementation, we use `std::vector<uint64_t>` to store large integers. We also use `base` as 1e9, so each element in the vector can store up to 9 digits. The `str_to_vec` and `vec_to_str` functions convert the input strings to a `std::vector<uint64_t>` representation and back, respectively.

Note that this version only handles non-negative integers. If you need to support negative integers, you can add a sign variable and handle it similarly to the previous `std::string` version. 
*/

